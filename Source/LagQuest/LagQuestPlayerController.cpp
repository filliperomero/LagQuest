// Copyright Epic Games, Inc. All Rights Reserved.

#include "LagQuestPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "LagQuest.h"
#include "Player/Lq_PlayerState.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "UI/Lq_PickupCountWidget.h"

void ALagQuestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogLagQuest, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	if (!IsLocalController()) return;

	PickupCountWidget = CreateWidget<ULq_PickupCountWidget>(this, PickupCountWidgetClass);
	if (IsValid(PickupCountWidget))
	{
		PickupCountWidget->AddToViewport();
	}

	if (HasAuthority())
	{
		ALq_PlayerState* Lq_PlayerState = GetPlayerState<ALq_PlayerState>();
		if (!IsValid(Lq_PlayerState)) return;

		Lq_PlayerState->OnPickupCountChanged.AddDynamic(this, &ThisClass::OnPickupCountChanged);
	}
}

void ALagQuestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void ALagQuestPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsLocalController()) return;

	ALq_PlayerState* Lq_PlayerState = GetPlayerState<ALq_PlayerState>();
	if (!IsValid(Lq_PlayerState)) return;

	Lq_PlayerState->OnPickupCountChanged.AddDynamic(this, &ThisClass::OnPickupCountChanged);
}

void ALagQuestPlayerController::OnPickupCountChanged(int32 InCount)
{
	if (!IsValid(PickupCountWidget)) return;
	
	PickupCountWidget->SetPickupCount(InCount);
}
