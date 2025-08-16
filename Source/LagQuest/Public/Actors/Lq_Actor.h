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

public:
	virtual void Tick(float DeltaTime) override;
};
