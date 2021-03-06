#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SanwuFileManager.generated.h"
using namespace UF;
UCLASS()
class USanwuFileManager :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**移动文件位置*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|FileManager")
	static bool MoveFileTo(FString To, FString From);

	/**删除一个文件*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|FileManager")
	static bool DeleteFile(FString FilePath);

	/*获取文件夹列表*/
	UFUNCTION(BlueprintPure, Category = "Sanwu|FileManager")
	static TArray<FString> GetCurrentDirAllFolders(FString Dir);

	/*获取文件列表*/
	UFUNCTION(BlueprintPure, Category = "Sanwu|FileManager")
		static TArray<FString> GetCurrentDirAllFiles(FString Dir, FString Extension);

	/*加载数据*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|FileManager")
		static bool LoadDataFromFile(const FString& FullFilePath, FString& Content);

	/*保存数据*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|FileManager")
		static bool SaveDataToFile(const FString SaveFile, FString Content);
};