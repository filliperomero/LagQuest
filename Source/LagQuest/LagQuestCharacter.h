// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/Lq_Player.h"
#include "Logging/LogMacros.h"
#include "LagQuestCharacter.generated.h"

class ULq_HealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ALagQuestCharacter : public ACharacter, public ILq_Player
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** ILq_Player Interface */
	virtual USkeletalMeshComponent* GetSkeletalMesh_Implementation() const override;
	virtual void GrantArmor_Implementation(float ArmorAmount) override;
	virtual void IncrementPickupCount_Implementation() override;
	virtual void AddHealth_Implementation(float HealthAmount) override;
	/** ILq_Player Interface End */
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

public:

	/** Constructor */
	ALagQuestCharacter();	

protected:
	virtual void BeginPlay() override;

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Armor)
	float Armor { 0.f };

	UPROPERTY(ReplicatedUsing=OnRep_PickupCount)
	int32 PickupCount { 0 };

	/** General Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* GeneralInputAction;

	void OnGeneralInput();

	UFUNCTION()
	void OnRep_Armor();

	UFUNCTION()
	void OnRep_PickupCount(int32 PreviousValue);

	bool bReplicatePickupCount { false };

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULq_HealthComponent> HealthComponent;

	UFUNCTION(Client, Reliable)
	void Client_PrintMessage(const FString& Message);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PrintMessage(const FString& Message);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PrintMessage(const FString& Message);

	FTimerHandle RPCDelayTimer;

	void OnRPCDelayTimer();
};
