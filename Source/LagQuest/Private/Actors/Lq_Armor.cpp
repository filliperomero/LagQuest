// Copyright Fillipe Romero. All Rights Reserved.

#include "Actors/Lq_Armor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

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

	ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor);

	if (HasAuthority() && IsValid(OverlappedCharacter))
	{
		// AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SphereMesh->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HeadSocket);
		BootMesh_R->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightFootSocket);
		BootMesh_L->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftFootSocket);
	}
}

