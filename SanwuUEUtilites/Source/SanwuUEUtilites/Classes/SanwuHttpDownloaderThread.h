#pragma once
class UHttpDownloadManager;
class FSanwuHttpDownloaderThread : public FRunnable
{
public:
	FSanwuHttpDownloaderThread(UHttpDownloadManager* DownloadManager,int32 id,int32 StartMissionIndex ,int32 EndMissionIndex,FString url,FString des);
	virtual ~FSanwuHttpDownloaderThread();

	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;
private:
	FString MissionURL;
	UHttpDownloadManager* Manager;
	FString MissionContent;
	
	FRunnableThread* Thread;
	int32 StartWritePoint;
	FString DestinationPath;

	int32 StartMission;
	int32 EndMission;
	TSharedPtr<class IHttpRequest> RequestPtr;

	void DownloadLoop();

	void WriteDataToFile(const TArray<uint8>Data);
	void HandleMissonComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
