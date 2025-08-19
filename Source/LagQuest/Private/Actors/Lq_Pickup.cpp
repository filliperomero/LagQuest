// Copyright Fillipe Romero. All Rights Reserved.

#include "Actors/Lq_Pickup.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/Lq_Player.h"
#include "Player/Lq_PlayerState.h"

ALq_Pickup::ALq_Pickup()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetIsReplicated(true);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
}

void ALq_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor->HasAuthority()) return;

	// This will only happen on the server
	if (OtherActor->Implements<ULq_Player>())
	{
		ILq_Player::Execute_IncrementPickupCount(OtherActor);
		ILq_Player::Execute_AddHealth(OtherActor, HealthValue);
	}

	if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor); IsValid(OtherCharacter))
	{
		if (ALq_PlayerState* PlayerState = Cast<ALq_PlayerState>(OtherCharacter->GetPlayerState()); IsValid(PlayerState))
		{
			PlayerState->SetNumPickups(PlayerState->GetNumPickups() + 1);
		}
	}

	Destroy();
}

void ALq_Pickup::BeginPlay()
{
	Super::BeginPlay();
}
