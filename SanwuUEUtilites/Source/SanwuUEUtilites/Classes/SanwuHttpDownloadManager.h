#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SanwuHttpDownloaderThread.h"
#include "SanwuHttpDownloadManager.generated.h"
/*
下载文件到本地
*/
class UHttpDownloader;

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
public:
	FString GetMissionURL();
	FString GetMissonContent();
	FString GetDestinationPath();
	void HandlePieceDownload(int32 DownloadedByte);
	float DownloadPercent;
	void HandMissionPartComplete();
	TArray<FString>MissionPool;//任务池
private:

	void GetFileSize();

	FString url;//请求下载的文件的URL地址
	FString fileName;//保存到本地的文件名
	FString DirctoryPath;//保存路径（文件夹）
	FString DestinationPath;//最终路径
	//**************Parent************
	int32 FileTotalSize = 0;//文件总大小
	int32 FileDownloadedSize = 0;
	

	static UHttpDownloadManager* Manager;
	//HTTP请求完成或中断
	void HandleGetFileSize(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void UpdateTimer();
	FTimerHandle TimerHandle;

	UWorld* GameWorld;
	FCriticalSection MissionPoolCriticalSection;
	int32 MissionPartNum;
	int32 MissionPartCompleteNum;
	
};