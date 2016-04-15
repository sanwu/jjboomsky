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
	FString EndWritePointStr;
	FString StartWritePointStr;
	MissonContent.Split("-",&StartWritePointStr, &EndWritePointStr);
	StartWritePoint=FCString::Atoi(*StartWritePointStr);
	UE_LOG(LogHttpDownloader, Warning, TEXT("Mission %s Complete"), *MissonContent);
	if (FFileHelper::SaveArrayToFile(HttpResponse->GetContent(), *DestinationPath, &IFileManager::Get(), (uint32)StartWritePoint)) {
		Manager->HandlePieceDownload(HttpResponse->GetContentLength());
		FetchMission();
	}
	else {
		UE_LOG(LogHttpDownloader, Error, TEXT("Mission %s Write to file fail"), *MissonContent);
	}
	
}