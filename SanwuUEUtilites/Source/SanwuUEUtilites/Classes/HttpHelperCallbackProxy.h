#pragma once

#include "HttpHelperCallProxyBase.h"
#include "HttpHelperCallbackProxy.generated.h"



UCLASS(MinimalAPI)
class UHttpHelperCallbackProxy :public UHttpHelperCallProxyBase
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FHttpRequestDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FHttpRequestDelegate OnError;

	UFUNCTION(BlueprintCallable,Category="Sanwu|Utilites",meta=(BlueprintInternalUseOnly = "true"))
	static UHttpHelperCallbackProxy* SendHttpRequest(FString URL,EHttpType HttpType);

	virtual void Activate() override;
private:

};
