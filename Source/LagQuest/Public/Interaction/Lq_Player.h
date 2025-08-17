// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Lq_Player.generated.h"

UINTERFACE()
class ULq_Player : public UInterface
{
	GENERATED_BODY()
};

class LAGQUEST_API ILq_Player
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	USkeletalMeshComponent* GetSkeletalMesh() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GrantArmor(float ArmorAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncrementPickupCount();
};
