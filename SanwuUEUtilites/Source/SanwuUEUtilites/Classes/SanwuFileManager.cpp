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

TArray<FString> USanwuFileManager::GetCurrentDirAllFiles(FString Dir, FString Extension)
{
	TArray<FString> AllFiles;
	FString SearchDir = Dir + "*." + Extension; //test.zip
	IFileManager::Get().FindFiles(AllFiles, *SearchDir, true, false);
	
	TArray<FString> SearchFiles;
	FString SearchFile;
	for (int32 i = 0; i < AllFiles.Num(); i++)
	{
		SearchFile = Dir + AllFiles[i];
		SearchFiles.Add(SearchFile);
	}
	return SearchFiles;
}

bool USanwuFileManager::LoadDataFromFile(const FString& FullFilePath, FString& Content)
{
	if (!FFileHelper::LoadFileToString(Content, *FullFilePath))
	{
		return false;
	}
	if (Content.Len() <= 0)
	{
		return false;
	}
	return true;
}

bool USanwuFileManager::SaveDataToFile(const FString SaveFile, FString Content)
{
	if (!FFileHelper::SaveStringToFile(Content, *SaveFile, FFileHelper::EEncodingOptions::ForceUTF8))
	{
		return false;
	}
	return true;
}