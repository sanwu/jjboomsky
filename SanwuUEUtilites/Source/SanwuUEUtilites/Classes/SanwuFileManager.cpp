#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuFileManager.h"
bool USanwuFileManager::MoveFileTo(FString To, FString From)
{
	return IFileManager::Get().Move(*To, *From);
}
bool USanwuFileManager::DeleteFile(FString FilePath)
{
	return IFileManager::Get().Delete(*FilePath);
}

TArray<FString> USanwuFileManager::GetCurrentDirAllFolders(FString Dir)
{
	TArray<FString> AllFolders;
	FString SearchDir = Dir + "*";
	IFileManager::Get().FindFiles(AllFolders, *SearchDir, false, true);
	return AllFolders;
}