// Copyright Fillipe Romero. All Rights Reserved.


#include "Player/Lq_PlayerState.h"

#include "Net/UnrealNetwork.h"

ALq_PlayerState::ALq_PlayerState()
{
	SetNetUpdateFrequency(10.f);
}

void ALq_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NumPickups);
}

void ALq_PlayerState::SetNumPickups(const int32 Amount)
{
	NumPickups = Amount;

	OnPickupCountChanged.Broadcast(NumPickups);
}

void ALq_PlayerState::OnRep_NumPickups()
{
	OnPickupCountChanged.Broadcast(NumPickups);
}
