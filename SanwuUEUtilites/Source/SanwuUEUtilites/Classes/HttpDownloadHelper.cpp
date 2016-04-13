#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpDownloadHelper.h"
#include "Http.h"
DEFINE_LOG_CATEGORY_STATIC(LogHttpDownload, Warning, All);
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
	UE_LOG(LogHttpDownload, Warning, TEXT("SaveDir %s"),*(FPaths::GameSavedDir()/"Download"));
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
	int32 Length = HttpRequest->GetResponse()->GetContentLength();//这里获取的时候实时加载的大小，不是总资源大小，算百分比有问题！
	int32 ContentLength = HttpRequest->GetResponse()->GetContent().Num();

	ByteDownloaded = DownloadTotal;
	if (ByteDownloaded-ByteSaved>(1024*200) /*200KB*/)
	{
		TArray<uint8>Emp;
		TArray<uint8> & NeedSaveData = Emp;
		//Todo 分段保存，就是每次接收数据的时候判断一下，如果积累的数据存过200KB，就保存一下。
		//HttpRequest->GetResponse()->GetContent().CopyToEmpty(&NeedSaveData, ByteSaved, 1024 * 200);
	}

	SaveByteToFile(HttpRequest, UploadTotal, DownloadTotal);
	OnProgress.Broadcast("", DownloadTotal*1.0 /Length);
}
void UHttpDownloadHelper::SaveByteToFile(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal)
{
	//Todo 
	if (FFileHelper::SaveArrayToFile(HttpRequest->GetResponse()->GetContent(), 
		*(FPaths::GameSavedDir() / "Download/" + DirctoryPath / fileName))
		
		)
	{

	}
	
}
