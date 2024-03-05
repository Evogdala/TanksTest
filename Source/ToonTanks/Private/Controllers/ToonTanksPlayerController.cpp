// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ToonTanksPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}

void AToonTanksPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		PlayerEnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AToonTanksPlayerController::OnPauseGame);
	}
}

void AToonTanksPlayerController::OnPauseGame()
{
	UGameplayStatics::GetGameMode(this)->SetPause(this);
}
