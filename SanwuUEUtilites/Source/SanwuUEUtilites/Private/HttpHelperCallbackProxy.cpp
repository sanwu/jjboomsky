#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpHelperCallbackProxy.h"
UHttpHelperCallbackProxy::UHttpHelperCallbackProxy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}
UHttpHelperCallbackProxy* UHttpHelperCallbackProxy::SendHttpRequest(FString URL, EHttpType HttpType)
{
	UHttpHelperCallbackProxy* Proxy = NewObject<UHttpHelperCallbackProxy>();
	return Proxy;
}
void UHttpHelperCallbackProxy::Activate()
{

}