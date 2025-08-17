// Copyright Fillipe Romero. All Rights Reserved.

#include "Actors/Lq_Armor.h"

#include "Components/SphereComponent.h"
#include "Interaction/Lq_Player.h"

ALq_Armor::ALq_Armor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetIsReplicated(true);

	BootMesh_R = CreateDefaultSubobject<UStaticMeshComponent>("BootMeshR");
	BootMesh_R->SetupAttachment(RootComponent);
	BootMesh_R->SetIsReplicated(true);

	BootMesh_L = CreateDefaultSubobject<UStaticMeshComponent>("BootMeshL");
	BootMesh_L->SetupAttachment(RootComponent);
	BootMesh_L->SetIsReplicated(true);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
}

void ALq_Armor::BeginPlay()
{
	Super::BeginPlay();
}

void ALq_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALq_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor->HasAuthority()) return;

	// This will only happen on the server
	if (OtherActor->Implements<ULq_Player>())
	{
		USkeletalMeshComponent* CharacterMesh = ILq_Player::Execute_GetSkeletalMesh(OtherActor);
		
		// AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SphereMesh->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HeadSocket);
		BootMesh_R->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightFootSocket);
		BootMesh_L->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftFootSocket);

		ILq_Player::Execute_GrantArmor(OtherActor, ArmorAmount);
	}
}

