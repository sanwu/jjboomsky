#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SanwuHttpDownloadManager.h"
#include "SanwuHttpDownloader.generated.h"

UCLASS()
class UHttpDownloader : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Sanwu", meta = (BlueprintInternalUseOnly = "true"))
	static UHttpDownloader* Init(UHttpDownloadManager* Manager,int32 ID);

public:
	int32 ID;
	int32 StartWritePoint;
	FString MissonContent;
	FString MissonURL;
	FString DestinationPath;
private:
	UHttpDownloadManager* Manager;
	
	void WriteDataToFile(const TArray<uint8>Data);
	void FetchMission();
	void HandleMissonComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};