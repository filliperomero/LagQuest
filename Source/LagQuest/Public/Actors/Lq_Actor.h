// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lq_Actor.generated.h"

UCLASS()
class LAGQUEST_API ALq_Actor : public AActor
{
	GENERATED_BODY()

public:
	ALq_Actor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void Client_PrintActorName();

	UFUNCTION(Server, Reliable)
	void Server_PrintActorName();

	virtual void OnRep_Owner() override;

public:
	virtual void Tick(float DeltaTime) override;
};
