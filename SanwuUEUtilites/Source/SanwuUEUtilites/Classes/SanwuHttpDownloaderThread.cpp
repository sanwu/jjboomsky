#include "SanwuUEUtilitesPrivatePCH.h"
#include "IHttpRequest.h"
#include "IHttpResponse.h"
#include "HttpModule.h"
#include "SanwuHttpDownloaderThread.h"
#include "SanwuHttpDownloadManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHttpDownloaderThread, Warning, All);

FSanwuHttpDownloaderThread::FSanwuHttpDownloaderThread(
	UHttpDownloadManager* DownloadManager,
	int32 id,
	int32 StartMissionIndex, 
	int32 EndMissionIndex,
	FString url, 
	FString des)
{
	Manager = DownloadManager;
	MissionURL = url;
	MissionURL = DownloadManager->GetMissionURL();
	FString ThreadName = "SanwuHttpDownloaderThread" + FString::FromInt(id);
	StartMission = StartMissionIndex;
	EndMission = EndMissionIndex;
	DestinationPath = des;

	Thread=FRunnableThread::Create(this, *ThreadName, 1024 * 1024, EThreadPriority::TPri_AboveNormal);
	//UE_LOG(LogHttpDownloaderThread, Warning, TEXT("Thread id = %d  Start %d -- %d"),id,StartMissionIndex,EndMissionIndex);
}

void FSanwuHttpDownloaderThread::HandleMissonComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	HttpRequest->OnProcessRequestComplete().Unbind();
	if (bSucceeded)// 
	{
		FString EndWritePointStr;
		FString StartWritePointStr;
		FString ByteFlagStr;
		MissionContent.Split("-", &StartWritePointStr, &EndWritePointStr);
		StartWritePointStr.Split("bytes=", &ByteFlagStr, &EndWritePointStr);
		StartWritePoint = FCString::Atoi(*EndWritePointStr);

		WriteDataToFile(HttpResponse->GetContent());
	
	}
	else {
		//下载不成功以后的处理
		// Todo 把任务交还任务池，并重新下载
	}
}
void FSanwuHttpDownloaderThread::WriteDataToFile(const TArray<uint8>Data)
{
	FILE *Stream;
	if (fopen_s(&Stream, TCHAR_TO_UTF8(*DestinationPath), "rb+") == 0) {

		fseek(Stream, StartWritePoint, SEEK_SET);
		if (fwrite((char*)Data.GetData(), sizeof(char), Data.Num(), Stream) > 0)
		{
			fclose(Stream);
			UE_LOG(LogHttpDownloaderThread, Warning, TEXT("任务%s写入文件成功"),*MissionContent);
			StartMission++;
			Manager->HandMissionPartComplete();
			DownloadLoop();
		}
		else {
			UE_LOG(LogHttpDownloaderThread, Error, TEXT("任务 %s 下载失败"),*MissionContent);
		}
	}
	else {
		UE_LOG(LogHttpDownloaderThread, Error, TEXT("任务 %s 写入文件失败"),*MissionContent);
		WriteDataToFile(Data);
	}
}
FSanwuHttpDownloaderThread::~FSanwuHttpDownloaderThread()
{
	if (Thread != nullptr)
	{
		Thread->Kill(true);
		delete Thread;
	}
}
bool FSanwuHttpDownloaderThread::Init()
{
	return true;
}

uint32 FSanwuHttpDownloaderThread::Run()
{
	DownloadLoop();
	return 0;
}
void FSanwuHttpDownloaderThread::DownloadLoop()
{
	if (StartMission < EndMission)
	{
		//UE_LOG(LogHttpDownloader, Warning, TEXT("S = %d  E=%d"), StartMission,EndMission);
		if (IsValid(Manager))
		{
			MissionContent = Manager->MissionPool[StartMission];
			TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
			HttpRequest->OnProcessRequestComplete().BindRaw(this, &FSanwuHttpDownloaderThread::HandleMissonComplete);
			HttpRequest->SetURL(MissionURL);
			HttpRequest->SetVerb(TEXT("GET"));
			HttpRequest->SetHeader("Range", MissionContent);
			//UE_LOG(LogHttpDownloaderThread, Error, TEXT("任务 %s 开始下载"), *MissionContent);
			HttpRequest->ProcessRequest();
		}
	}
}
void FSanwuHttpDownloaderThread::Stop()
{
	
}

void FSanwuHttpDownloaderThread::Exit()
{
// 	if (Thread!=nullptr)
// 	{
// 		Thread->Kill(true);
// 		delete Thread;
// 	}
	
}

