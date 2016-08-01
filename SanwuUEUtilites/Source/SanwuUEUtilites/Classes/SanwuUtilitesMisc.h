#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SanwuUtilitesMisc.generated.h"

/**
 *
 */
using namespace UF;

UCLASS()
class  USanwuUtilitesMisc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "SanwuMisc")
	static void RestartGameClient();
};
