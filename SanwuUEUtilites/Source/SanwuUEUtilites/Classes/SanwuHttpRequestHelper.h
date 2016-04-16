#pragma once
#include "IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SanwuHttpRequestHelper.generated.h"

using namespace UF;
using namespace UP;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSanwuHttpRequestDelegate, FString, Content, int32, StatusCode);

UENUM()
enum SanwuHttpRequestType
{
	GET,
	POST
};

UCLASS()
class USanwuHttpRequestHelper : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Sanwu|Http", meta = (BlueprintInternalUseOnly = "true"))
	static USanwuHttpRequestHelper* HttpRequestString(FString url,SanwuHttpRequestType Type,FString Content);

	UPROPERTY(BlueprintAssignable)
	FSanwuHttpRequestDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSanwuHttpRequestDelegate OnFail;

public:

private:
	void Start(FString URL, SanwuHttpRequestType Type, FString Content);
	void HandleRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};