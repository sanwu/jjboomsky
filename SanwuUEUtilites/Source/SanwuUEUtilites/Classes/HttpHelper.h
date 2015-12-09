#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpHelper.generated.h"

/**
 
 */
using namespace UF;
DECLARE_DELEGATE_TwoParams(FOnHttpRequstComplete,bool,FString)
UCLASS()
class SANWUUEUTILITES_API UHttpHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Sanwu|Http",meta=(DisplayName="Send HttpRequest"))
	static bool HttpRequest_NEW(FString url, FHitResult& OutHit);
};
