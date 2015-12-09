#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScreenShootTool.generated.h"

/**
 * 这是一个用来实现蓝图里截图功能的扩展
 *因为目前（4.10）为止，虽然能实现截图，用ExecConsoleCommand节点。 但是它不能获取截图的返回值
 *而且不能手动设置截图的名字
 *所以写了此功能
 */
using namespace UF;

UCLASS()
class SANWUUEUTILITES_API UScreenShootTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	截图，并设置名字
	*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|SanwuUEUtilites")
	static FString TakeScreenShoot(FString picName,bool bUnique=true);

	/**
	获取截图默认保存的路径
	*/
	UFUNCTION(BlueprintCallable, Category = "Sanwu|SanwuUEUtilites")
	static FString GetBaseScreenShotPath();
};
