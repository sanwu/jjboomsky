#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpDownloadHelper.h"
#include "Http.h"

UHttpDownloadHelper::UHttpDownloadHelper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UHttpDownloadHelper* UHttpDownloadHelper::DownloadFile(FString url, FString FileName, FString Dirctory)
{
	UHttpDownloadHelper* Downloader = NewObject<UHttpDownloadHelper>();
	Downloader->url = url;
	Downloader->fileName = FileName;
	Downloader->DirctoryPath = Dirctory;
	Downloader->Start();
	return Downloader;
}
void UHttpDownloadHelper::Start()
{
	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpDownloadHelper::HandleFileRequest);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHttpDownloadHelper::HandleFileProgress);
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
}
void UHttpDownloadHelper::HandleFileRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetContentLength() > 0)
	{
		OnSuccess.Broadcast("",1);
	}
	OnFail.Broadcast("",0);
}
void UHttpDownloadHelper::HandleFileProgress(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal)
{
	int32 Length = HttpRequest->GetResponse()->GetContentLength();
	int32 ContentLength = HttpRequest->GetResponse()->GetContent().Num();
	OnProgress.Broadcast("",ContentLength);
}
void UHttpDownloadHelper::SaveByteToFile(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal)
{
	//Todo 
}