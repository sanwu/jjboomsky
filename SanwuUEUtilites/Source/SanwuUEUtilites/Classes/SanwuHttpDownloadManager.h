#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SanwuHttpDownloadManager.generated.h"
/*
下载文件到本地
*/
class UHttpDownloader;

using namespace UF;
using namespace UP;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDownloadFileDelegate, FString, DestinationPath, float, DownloadPercent);

UENUM()
enum class EDownLoadBaseDir : uint8
{
	GameDir,
	EngineDir,
	SaveDir,
	UserDir
};

UCLASS()
class UHttpDownloadManager : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Sanwu", meta = (BlueprintInternalUseOnly = "true"))
	static UHttpDownloadManager* DownloadFile(FString url,EDownLoadBaseDir basePath, FString relateve_path);

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnFail;

	UPROPERTY(BlueprintAssignable)
	FDownloadFileDelegate OnProgress;

public:

private:
	void StartMission();
	FString url;//请求下载的文件的URL地址
	FString DestinationPath;//最终路径
	//**************Parent************
	int32 FileTotalSize = 0;//文件总大小
	int32 FileDownloadedSize = 0;

	//HTTP请求完成或中断
	void HandleHttpCompelete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void HandleHttpProgress(FHttpRequestPtr req, int32 uploaded, int32 downloaded);

	
};