// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "MyProject.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "HealthComponent.h"

void AMyProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogMyProject, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AMyProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		if (InputComponent)
		{
			// Прив'язуємо клавішу F до функції OnFKeyPressed (спрацює при натисканні IE_Pressed)
			InputComponent->BindKey(EKeys::F, IE_Pressed, this, &AMyProjectPlayerController::OnFKeyPressed);

			// Прив'язуємо клавішу G до функції OnGKeyPressed
			InputComponent->BindKey(EKeys::G, IE_Pressed, this, &AMyProjectPlayerController::OnGKeyPressed);
		}
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool AMyProjectPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}


void AMyProjectPlayerController::OnFKeyPressed()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		UHealthComponent* HealthComp = ControlledPawn->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->ServerApplyDamage(10.0f);
		}
	}
}

void AMyProjectPlayerController::OnGKeyPressed()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		UHealthComponent* HealthComp = ControlledPawn->FindComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->ServerApplyDamage(-99999.0f);
		}
	
	}
}