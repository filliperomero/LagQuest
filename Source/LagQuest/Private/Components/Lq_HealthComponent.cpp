// Copyright Fillipe Romero. All Rights Reserved.

#include "Components/Lq_HealthComponent.h"
#include "Net/UnrealNetwork.h"

ULq_HealthComponent::ULq_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void ULq_HealthComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Health);
}

void ULq_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULq_HealthComponent::OnRep_Health(float OldHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Health: %f (OnRep)"), Health));
}
