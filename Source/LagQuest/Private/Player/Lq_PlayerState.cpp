// Copyright Fillipe Romero. All Rights Reserved.


#include "Player/Lq_PlayerState.h"

#include "Net/UnrealNetwork.h"

void ALq_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NumPickups);
}
