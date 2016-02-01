#include "SanwuUEUtilitesPrivatePCH.h"
#include "HttpHelperCallProxyBase.h"

UHttpHelperCallProxyBase::UHttpHelperCallProxyBase( const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetFlags(RF_StrongRefOnFrame);
}
void UHttpHelperCallProxyBase::Activate()
{

}