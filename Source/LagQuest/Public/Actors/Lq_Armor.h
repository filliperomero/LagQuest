// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lq_Armor.generated.h"

class USphereComponent;

UCLASS()
class LAGQUEST_API ALq_Armor : public AActor
{
	GENERATED_BODY()

public:
	ALq_Armor();
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BootMesh_L;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BootMesh_R;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditAnywhere, Category = "Lag Quest")
	FName HeadSocket { NAME_None };

	UPROPERTY(EditAnywhere, Category = "Lag Quest")
	FName LeftFootSocket { NAME_None };

	UPROPERTY(EditAnywhere, Category = "Lag Quest")
	FName RightFootSocket { NAME_None };
};
