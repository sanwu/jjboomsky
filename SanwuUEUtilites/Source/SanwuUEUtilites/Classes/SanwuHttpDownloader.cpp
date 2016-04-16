#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuHttpDownloader.h"
#include "Http.h"
DEFINE_LOG_CATEGORY_STATIC(LogHttpDownloader, Warning, All);
UHttpDownloader::UHttpDownloader(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
UHttpDownloader* UHttpDownloader::Init(UHttpDownloadManager* Manager,int32 ID)
{
	UHttpDownloader* Downloader = NewObject<UHttpDownloader>();
	Downloader->ID = ID;
	Downloader->MissonURL = Manager->GetMissionURL();
	Downloader->Manager = Manager;
	Downloader->DestinationPath = Manager->GetDestinationPath();
	Downloader->FetchMission();
	return Downloader;
}
void UHttpDownloader::FetchMission()
{
	MissonContent = Manager->GetMissonContent();
	if (MissonContent.Len()>0)
	{
		TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpDownloader::HandleMissonComplete);
		HttpRequest->SetURL(MissonURL);
		HttpRequest->SetVerb(TEXT("GET"));
		HttpRequest->SetHeader("Range", MissonContent);
		HttpRequest->ProcessRequest();
	}
}
void UHttpDownloader::HandleMissonComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	
	if (bSucceeded)// 
	{
		FString EndWritePointStr;
		FString StartWritePointStr;
		FString ByteFlagStr;
		MissonContent.Split("-", &StartWritePointStr, &EndWritePointStr);
		StartWritePointStr.Split("bytes=", &ByteFlagStr, &EndWritePointStr);
		StartWritePoint = FCString::Atoi(*EndWritePointStr);

		WriteDataToFile(HttpResponse->GetContent());
		return;
	}
	else {
		//下载不成功以后的处理
		// Todo 把任务交还任务池，并重新下载
	}

	
}
void UHttpDownloader::WriteDataToFile(const TArray<uint8>Data)
{
	FILE *Stream;
	if (fopen_s(&Stream, TCHAR_TO_UTF8(*DestinationPath), "rb+") == 0) {
		
		fseek(Stream, StartWritePoint,SEEK_SET);
		
		if (fwrite((char*)Data.GetData(), sizeof(char), Data.Num(), Stream) > 0)
		{
			fclose(Stream);
			UE_LOG(LogHttpDownloader, Warning, TEXT("Write %s Complete  Size=%d"), *MissonContent, Data.Num());
			Manager->HandlePieceDownload(Data.Num());
			FetchMission();
		}else{
			UE_LOG(LogHttpDownloader, Error, TEXT("Write %s Fail  Size=%d"), *MissonContent, Data.Num());
		}
		
		
	}
	else {
		UE_LOG(LogHttpDownloader, Error, TEXT("Mission %s Write to file fail"), *MissonContent);
		WriteDataToFile(Data);
	}
}