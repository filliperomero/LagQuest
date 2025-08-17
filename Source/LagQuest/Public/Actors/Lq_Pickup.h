// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lq_Pickup.generated.h"

class USphereComponent;

UCLASS()
class LAGQUEST_API ALq_Pickup : public AActor
{
	GENERATED_BODY()

public:
	ALq_Pickup();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;
};
