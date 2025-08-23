// Copyright Fillipe Romero. All Rights Reserved.


#include "Game/Lq_GameMode.h"

#include "Game/Lq_GameState.h"

ALq_GameMode::ALq_GameMode()
{
	bDelayedStart = true;
	bUseSeamlessTravel = true;
}

void ALq_GameMode::StartMatch()
{
	Super::StartMatch();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "The match has started.");
}

void ALq_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ALq_GameState* Lq_GameState = GetGameState<ALq_GameState>();

	if (IsValid(Lq_GameState))
	{
		Lq_GameState->AddTeamMember(NewPlayer);
	}
}

void ALq_GameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MatchStartTimer, this, &ThisClass::StartDelayFinished, MatchStartDelay);
}

void ALq_GameMode::StartDelayFinished()
{
	StartMatch();
}
