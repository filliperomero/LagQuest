// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Lq_MultiplayerUtils.generated.h"

UCLASS()
class LAGQUEST_API ULq_MultiplayerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Lag Quest - Utilities")
	static void PrintLocalNetRole(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Lag Quest - Utilities")
	static void PrintRemoteNetRole(AActor* Actor);
};
