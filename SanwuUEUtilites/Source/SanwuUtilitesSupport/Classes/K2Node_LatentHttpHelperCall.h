#pragma once

#include "K2Node_LatentHttpHelperCall.generated.h"

//这个类用来把基于HttpHelperCallProxyBase的类里面的函数显示在蓝图里
UCLASS()
class SANWUUTILITESSUPPORT_API UK2Node_LatentHttpHelperCall : public UK2Node_BaseAsyncTask
{
	GENERATED_UCLASS_BODY()

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
};