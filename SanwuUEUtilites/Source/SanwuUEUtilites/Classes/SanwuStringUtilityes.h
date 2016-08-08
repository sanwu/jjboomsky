#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SanwuStringUtilityes.generated.h"

/**
 *
 */
using namespace UF;

UCLASS()
class SANWUUEUTILITES_API USanwuStringUtilityes: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**把String转化为Array，根据一个标志*/
	UFUNCTION(BlueprintCallable, Category = "SanwuString")
	static TArray<FString> SplitStringToArray(FString SRC, FString Arg);

	UFUNCTION(BlueprintCallable, Category = "Sanwu|Utilityes")
	static class UTexture2D* GetTexture2DFromDiskFile(const FString& FilePath);
};
