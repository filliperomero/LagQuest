// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lq_HealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LAGQUEST_API ULq_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULq_HealthComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	float Health { 100.f };

	UFUNCTION()
	void OnRep_Health(float OldHealth);

public:
	void SetHealth(const float InHealth) { Health = InHealth; }
	float GetHealth() const { return Health; }
};
