// Copyright Fillipe Romero. All Rights Reserved.

#include "Actors/Lq_Actor.h"

ALq_Actor::ALq_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bNetLoadOnClient = true;
	bReplicates = true;
	SetReplicatingMovement(true);
}

void ALq_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Client_PrintActorName();
	}

	const bool bAuth = HasAuthority();
	const ENetRole LocalRole = GetLocalRole();
}

void ALq_Actor::Client_PrintActorName_Implementation()
{
	FString MessageString = HasAuthority() ? "Server: " : "Client: ";
	MessageString += GetName();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, MessageString);
}

void ALq_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
