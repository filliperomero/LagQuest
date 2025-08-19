// Copyright Fillipe Romero. All Rights Reserved.


#include "Game/Lq_GameState.h"

#include "Net/UnrealNetwork.h"

void ALq_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, TeamOne);
	DOREPLIFETIME(ThisClass, TeamTwo);
}

void ALq_GameState::AddTeamMember(APlayerController* PlayerController)
{
	if (TeamOne.Num() > TeamTwo.Num())
	{
		TeamTwo.Add(PlayerController);
	}
	else
	{
		TeamOne.Add(PlayerController);
	}
}

bool ALq_GameState::IsTeamOne(APlayerController* PlayerController) const
{
	return TeamOne.Contains(PlayerController);
}
