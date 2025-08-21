// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Lq_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupCountChanged, int32, Count);

UCLASS()
class LAGQUEST_API ALq_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ALq_PlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FPickupCountChanged OnPickupCountChanged;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_NumPickups)
	int32 NumPickups { 0 };

public:
	int32 GetNumPickups() const { return NumPickups; }
	void SetNumPickups(const int32 Amount);

	UFUNCTION()
	void OnRep_NumPickups();
};
