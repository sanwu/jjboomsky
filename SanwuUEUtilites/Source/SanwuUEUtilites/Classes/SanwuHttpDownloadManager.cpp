#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuHttpDownloadManager.h"
#include "Http.h"

DEFINE_LOG_CATEGORY_STATIC(LogHttpDownload, Warning, All);

UHttpDownloadManager* UHttpDownloadManager::Manager;

UHttpDownloadManager::UHttpDownloadManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHttpDownloadManager* UHttpDownloadManager::DownloadFile(FString url, EDownLoadBaseDir basePath, FString relateve_path)
{
	UHttpDownloadManager* Downloader = NewObject<UHttpDownloadManager>();
	Downloader->url = url;
	FString FileName = FPaths::GetCleanFilename(relateve_path);
	
	FString bPath;
	switch (basePath) {
	case EDownLoadBaseDir::GameDir:
		bPath = FPaths::GameDir();
		break;
	case EDownLoadBaseDir::EngineDir:
		bPath = FPaths::EngineDir();
		break;
	case EDownLoadBaseDir::SaveDir:
		bPath = FPaths::GameSavedDir();
		break;
	case EDownLoadBaseDir::UserDir:
		bPath = FPaths::GameUserDir();
		break;
	}
	bPath = FPaths::ConvertRelativePathToFull(bPath);
	bPath = FPaths::Combine(bPath, relateve_path);
	FString desPath = FPaths::GetPath(bPath);
	FString desName = FPaths::GetCleanFilename(bPath);
	UE_LOG(LogHttpDownload, Warning, TEXT("desPath = %s  desName = %s   =>%s"), *desPath,*desName,*bPath);
	if (IFileManager::Get().DirectoryExists(*desPath) == false)
	{
		if (IFileManager::Get().MakeDirectory(*desPath, true) ==false) {
			Downloader->OnFail.Broadcast("Make dir failed", 0);
		}
	}
	Downloader->url = url;
	Downloader->DestinationPath = bPath;
	Downloader->GetFileSize();
	return Downloader;
}
void UHttpDownloadManager::GetFileSize()
{
	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpDownloadManager::HandleGetFileSize);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHttpDownloadManager::HandleHttpProgress);
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader("Range", "bytes=0-");
	HttpRequest->ProcessRequest();

	FArchive* F = IFileManager::Get().CreateFileWriter(*DestinationPath);
	F->Serialize(TCHAR_TO_UTF8(*DestinationPath), DestinationPath.Len());
	F->Close();
}
void UHttpDownloadManager::HandleHttpProgress(FHttpRequestPtr req, int32 uploaded, int32 downloaded) {
	UE_LOG(LogHttpDownload, Warning, TEXT("Download Progress %d   %d"),uploaded,downloaded);
	UE_LOG(LogHttpDownload, Warning, TEXT("Chunk Size =  %d "), req->GetResponse()->GetContent().Num());
	
}
void UHttpDownloadManager::HandleGetFileSize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded) {
		UE_LOG(LogHttpDownload, Warning, TEXT("获取下载目标文件信息失败，请检查网络"));
		OnFail.Broadcast("获取下载目标文件信息失败，请检查网络", 0);
		return;
	}
	int32 ResponseCode = HttpResponse->GetResponseCode();
	if (ResponseCode/200==1)
	{
		FString ContentRangeStr=HttpResponse->GetHeader("Content-Range");
		FString SplitLeftStr;
		FString SplitRightStr;
		ContentRangeStr.Split("/", &SplitLeftStr, &SplitRightStr);
		if (SplitRightStr.Len()>0)
		{
			FileTotalSize =FCString::Atoi(*SplitRightStr);
			//FileTotalSize = 201;
			//创建任务文件
			FILE *Stream;
			if (
				fopen_s(&Stream,TCHAR_TO_UTF8( *GetDestinationPath()),"wb+")==0
				) {
				fseek(Stream, FileTotalSize - 1, SEEK_SET);
				fputc(EOF, Stream);
				fclose(Stream);
			}
			//填充任务池
 			MissionPool.Empty(); //1024*500=512000  500KB一个任务
			if (FileTotalSize>512000)
			{
				int32 MissonNum = FileTotalSize / 512000;
				MissonNum++;
				for (int32 k = 0; k < MissonNum; k++)
				{
					int32 StartPoint = k * 512000;
					int32 EndPoint = StartPoint + 512000 - 1;
					FString StartStr = FString::FromInt(StartPoint);
					FString EndStr;
					if (EndPoint > FileTotalSize)
					{
						EndStr = "";
					}
					else {
						EndStr = FString::FromInt(EndPoint);
					}
					MissionPool.Add("bytes="+StartStr + "-" + EndStr);
				}
			}
			else {
				MissionPool.Add("bytes=0-");
			}
		}
		MissionPartNum = MissionPool.Num();
		//new FSanwuHttpDownloaderThread(Manager);
// 		MissionPool.Empty();
// 		MissionPool.Add("bytes=0-99");
// 		MissionPool.Add("bytes=100-199");


		///
		const TIndirectArray<FWorldContext>WorldContexts = GEngine->GetWorldContexts();
		for (FWorldContext context : WorldContexts)
		{
			if (context.World()->IsGameWorld())
			{
				GameWorld = context.World();
			}
		}
		
		if (GameWorld!=nullptr)
		{
			GameWorld->GetTimerManager().SetTimer(TimerHandle, this, &UHttpDownloadManager::UpdateTimer, 2.0f, true);
		}
		else {
			UE_LOG(LogHttpDownload, Warning, TEXT("获取World失败"));
		}
		////

		MissionPartCompleteNum = 0;

		int32 ThreadNum = 10;
		if (MissionPool.Num()>ThreadNum)
		{
			int32 a = MissionPool.Num() / ThreadNum;
			for (int32 d = 0; d < ThreadNum; d++)
			{
				int32 S = d*a;
				int32 E = d*a + a;
				if (E<MissionPool.Num()&&d==ThreadNum-1)
				{
					E = MissionPool.Num();
				}
				new FSanwuHttpDownloaderThread(Manager, d ,S,E,GetMissionURL(),GetDestinationPath());
			}
		}
		else {
			for (int32 c=0;c<MissionPool.Num();c++)
			{
				new FSanwuHttpDownloaderThread(Manager, c, c, c, GetMissionURL(), GetDestinationPath());
			}

		}

		
	}
}
void UHttpDownloadManager::UpdateTimer()
{
	UE_LOG(LogHttpDownload, Warning, TEXT("完成数量%d  总量%d"),MissionPartCompleteNum, MissionPartNum);
	OnProgress.Broadcast(DestinationPath, MissionPartCompleteNum*1.0/MissionPartNum);
	if (MissionPartCompleteNum ==MissionPartNum)
	{
		OnSuccess.Broadcast(GetDestinationPath(), 1);
		GameWorld->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UHttpDownloadManager::HandMissionPartComplete()
{
	FScopeLock Lock(&MissionPoolCriticalSection);
	MissionPartCompleteNum++;
	//UE_LOG(LogHttpDownload, Warning, TEXT("完成数量%d "), MissionPartCompleteNum);
}

FString UHttpDownloadManager::GetMissionURL()
{
	return url;
}
FString UHttpDownloadManager::GetMissonContent()
{
	if (MissionPool.Num()<1)
	{
		return "";
	}

	FString Misson = MissionPool[0];
	MissionPool.RemoveAt(0);
	return Misson;
}
FString UHttpDownloadManager::GetDestinationPath()
{
	return FPaths::GameSavedDir() / "Download/" + DirctoryPath / fileName;
}
void UHttpDownloadManager::HandlePieceDownload(int32 DownloadedByte)
{
	FileDownloadedSize += DownloadedByte;
	OnProgress.Broadcast(DestinationPath, FileDownloadedSize*1.0 / FileTotalSize);
	if (FileDownloadedSize==FileTotalSize)
	{
		OnSuccess.Broadcast(GetDestinationPath(), 1);
	}
}