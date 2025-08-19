// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Lq_GameState.generated.h"

UCLASS()
class LAGQUEST_API ALq_GameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void AddTeamMember(APlayerController* PlayerController);
	bool IsTeamOne(APlayerController* PlayerController) const;

private:
	UPROPERTY(Replicated)
	TArray<TObjectPtr<APlayerController>> TeamOne;

	UPROPERTY(Replicated)
	TArray<TObjectPtr<APlayerController>> TeamTwo;
};
