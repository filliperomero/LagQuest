// Copyright Epic Games, Inc. All Rights Reserved.

#include "LagQuestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LagQuest.h"
#include "Actors/Lq_Actor.h"
#include "Components/Lq_HealthComponent.h"
#include "Game/Lq_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/Lq_PlayerState.h"

USkeletalMeshComponent* ALagQuestCharacter::GetSkeletalMesh_Implementation() const
{
	return GetMesh();
}

void ALagQuestCharacter::GrantArmor_Implementation(float ArmorAmount)
{
	Armor += ArmorAmount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Armor: %f"), Armor));
}

void ALagQuestCharacter::IncrementPickupCount_Implementation()
{
	++PickupCount;
}

void ALagQuestCharacter::AddHealth_Implementation(float HealthAmount)
{
	if (!IsValid(HealthComponent)) return;

	HealthComponent->SetHealth(HealthComponent->GetHealth() + HealthAmount);
}

ALagQuestCharacter::ALagQuestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	HealthComponent = CreateDefaultSubobject<ULq_HealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
}

void ALagQuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALagQuestCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ALagQuestCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALagQuestCharacter::Look);

		// General
		EnhancedInputComponent->BindAction(GeneralInputAction, ETriggerEvent::Started, this, &ThisClass::OnGeneralInput);

		// Server Travel
		EnhancedInputComponent->BindAction(ServerTravelAction, ETriggerEvent::Started, this, &ThisClass::TravelToDestinationMap);
	}
	else
	{
		UE_LOG(LogLagQuest, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALagQuestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ALagQuestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ALagQuestCharacter::TravelToDestinationMap()
{
	if (HasAuthority())
	{
		GetWorld()->ServerTravel(TEXT("DestinationMap"));
	}
}

void ALagQuestCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ALagQuestCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ALagQuestCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ALagQuestCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ALagQuestCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(ThisClass, Armor, COND_OwnerOnly);
	
	DOREPLIFETIME_CONDITION(ThisClass, PickupCount, COND_Custom);
}

void ALagQuestCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	// If bReplicatePickupCount changes value, PickupCount will change replication status.
	// NOTE - The value of bReplicatePickupCount only matters on the server.
	DOREPLIFETIME_ACTIVE_OVERRIDE(ThisClass, PickupCount, bReplicatePickupCount);
}

void ALagQuestCharacter::OnGeneralInput()
{
	// bReplicatePickupCount = !bReplicatePickupCount;
	//
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Armor: %f"), Armor));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Pickup Count: %d"), PickupCount));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("bReplicatePickupCount: %d"), bReplicatePickupCount));
	//
	// Server_PrintMessage("");

	if (ALq_GameState* GameState = Cast<ALq_GameState>(UGameplayStatics::GetGameState(this)); IsValid(GameState))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()); IsValid(PlayerController))
		{
			FString TeamMessage= "Team ";
			if (GameState->IsTeamOne(PlayerController))
			{
				TeamMessage += "One";
			}
			else
			{
				TeamMessage += "Two";
			}

			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Cyan, TeamMessage);
		}
	}

	if (ALq_PlayerState* PS = GetPlayerState<ALq_PlayerState>(); IsValid(PS))
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Blue, FString::Printf(TEXT("Num Pickups: %d (Player State)"), PS->GetNumPickups()));
	}
}

void ALagQuestCharacter::OnRep_Armor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Armor: %f (OnRep)"), Armor));
}

void ALagQuestCharacter::OnRep_PickupCount(int32 PreviousValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Previous Pickup Count: %d (OnRep)"), PreviousValue));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Pickup Count: %d (OnRep)"), PickupCount));
}

void ALagQuestCharacter::OnRPCDelayTimer()
{
	if (HasAuthority())
	{
		Client_PrintMessage("This should run on the owning Client.");

		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		
		GetWorld()->SpawnActor<ALq_Actor>(GetActorLocation(), GetActorRotation(), SpawnParameters);

		Multicast_PrintMessage("Print this on the server and all relevant clients.");
	}
}

void ALagQuestCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(RPCDelayTimer, this, &ThisClass::OnRPCDelayTimer, 5.f, false);
}

void ALagQuestCharacter::Client_PrintMessage_Implementation(const FString& Message)
{
	FString MessageString = HasAuthority() ? "Server: " : "Client: ";
	MessageString += Message;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, MessageString);
}

void ALagQuestCharacter::Server_PrintMessage_Implementation(const FString& Message)
{
	FString MessageString = HasAuthority() ? "Server: " : "Client: ";
	MessageString += Message;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, MessageString);
}

bool ALagQuestCharacter::Server_PrintMessage_Validate(const FString& Message)
{
	return !Message.IsEmpty();
}

void ALagQuestCharacter::Multicast_PrintMessage_Implementation(const FString& Message)
{
	FString MessageString = HasAuthority() ? "Server: " : "Client: ";
	MessageString += Message;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, MessageString);
}