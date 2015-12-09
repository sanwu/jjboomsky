#pragma once
#include "HttpHelperCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpRequestDelegate);

UENUM()
enum EHttpType
{
	GET,
	POST,
};

UCLASS(MinimalAPI)
class  UHttpHelperCallProxyBase :public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Sanwu|Utilites")
	virtual void Activate();
};