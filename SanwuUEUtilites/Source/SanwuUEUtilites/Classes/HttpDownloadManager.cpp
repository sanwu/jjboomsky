#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpDownloadManager.h"
#include "Http.h"

DEFINE_LOG_CATEGORY_STATIC(LogHttpDownload, Warning, All);
UHttpDownloadManager::UHttpDownloadManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHttpDownloadManager* UHttpDownloadManager::DownloadFile(FString url, FString FileName, FString Dirctory)
{
	UHttpDownloadManager* Downloader = NewObject<UHttpDownloadManager>();
	Downloader->url = url;
	Downloader->fileName = FileName;
	Downloader->DirctoryPath = Dirctory;
	Downloader->GetFileSize();
	return Downloader;
}
void UHttpDownloadManager::GetFileSize()
{
	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpDownloadManager::HandleGetFileSize);
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(TEXT("GET"));
	//HttpRequest->SetHeader("Range", "bytes=0-1");
	HttpRequest->ProcessRequest();
}
void UHttpDownloadManager::HandleGetFileSize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
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
	}
}
void UHttpDownloadManager::SaveByteToFile(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal)
{
	//Todo 
	if (FFileHelper::SaveArrayToFile(HttpRequest->GetResponse()->GetContent(), 
		*(FPaths::GameSavedDir() / "Download/" + DirctoryPath / fileName))
		)
	{

	}
	
}
