#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpDownloadHelper.generated.h"
/*
下载文件到本地
*/
using namespace UF;
using namespace UP;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDownloadFileDelegate, FString, DestinationPath, float, DownloadPercent);

UCLASS()
class UHttpDownloadHelper : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Sanwu", meta = (BlueprintInternalUseOnly = "true"))
	static UHttpDownloadHelper* DownloadFile(FString url,FString FileName,FString Dirctory);

	void Start();

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnFail;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnProgress;
private:
	FString url;//请求下载的文件的URL地址
	FString fileName;//保存到本地的文件名
	FString DirctoryPath;//保存路径（文件夹）

	int32 ByteDownloaded = 0;
	int32 ByteSaved = 0;
	

	//HTTP请求完成或中断
	void HandleFileRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	//处理接收到Http返回的数据
	void HandleFileProgress(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal);

	//把接收到的二进制数据保存到指定的文件里
	void SaveByteToFile(FHttpRequestPtr HttpRequest, int32 UploadTotal, int32 DownloadTotal);
};