// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Lq_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class LAGQUEST_API ALq_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALq_GameMode();

	virtual void StartMatch() override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle MatchStartTimer;

	UPROPERTY(EditDefaultsOnly)
	float MatchStartDelay { 5.f };

	void StartDelayFinished();
};
