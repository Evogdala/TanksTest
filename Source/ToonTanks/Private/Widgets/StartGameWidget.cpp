// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StartGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ToonTanksGameMode.h"


void UStartGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (AToonTanksGameMode* ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		Countdown = ToonTanksGameMode->GetStartDelay();
	}
}
