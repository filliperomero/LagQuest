// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Lq_PlayerState.generated.h"

UCLASS()
class LAGQUEST_API ALq_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
	int32 NumPickups { 0 };

public:
	int32 GetNumPickups() const { return NumPickups; }
	void SetNumPickups(const int32 Amount) { NumPickups = Amount; }
};
