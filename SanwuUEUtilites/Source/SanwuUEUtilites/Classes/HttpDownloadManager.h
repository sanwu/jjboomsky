#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpDownloadManager.generated.h"
/*
下载文件到本地
*/
using namespace UF;
using namespace UP;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDownloadFileDelegate, FString, DestinationPath, float, DownloadPercent);

UCLASS()
class UHttpDownloadManager : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Sanwu", meta = (BlueprintInternalUseOnly = "true"))
	static UHttpDownloadManager* DownloadFile(FString url,FString FileName,FString Dirctory);

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnFail;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnProgress;

	UHttpDownloadManager* ParentDownloader;

private:

	void GetFileSize();

	FString url;//请求下载的文件的URL地址
	FString fileName;//保存到本地的文件名
	FString DirctoryPath;//保存路径（文件夹）
	//**************Parent************
	int32 FileTotalSize = 0;//文件总大小
	TArray<FString>MissionPool;
	FString CurrentMisson;
	
	//**************Child**************
	void HandChildMissonComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	//HTTP请求完成或中断
	void HandleGetFileSize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	//把接收到的二进制数据保存到指定的文件里
	void SaveByteToFile(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal);
};