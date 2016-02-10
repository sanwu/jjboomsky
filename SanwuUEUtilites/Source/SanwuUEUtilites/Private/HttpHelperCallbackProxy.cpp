#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpHelperCallbackProxy.h"
UHttpHelperCallbackProxy::UHttpHelperCallbackProxy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}
UHttpHelperCallbackProxy* UHttpHelperCallbackProxy::SendHttpRequest(FString URL, EHttpType HttpType)
{
	UHttpHelperCallbackProxy* Proxy = NewObject<UHttpHelperCallbackProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);
	return Proxy;
}
void UHttpHelperCallbackProxy::Activate()
{

}