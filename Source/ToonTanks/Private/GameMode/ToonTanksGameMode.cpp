// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ToonTanksGameMode.h"
#include "Weaponry/Tank.h"
#include "Weaponry/TowerTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor->IsA<ATank>())
	{
		ATank* Tank = Cast<ATank>(DeadActor);
		if (Tank && ToonTanksPlayerController)
		{
			Tank->HandleDestruction();

			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (DeadActor->IsA<ATowerTurret>())
	{

		if (ATowerTurret* TowerTurret = Cast<ATowerTurret>(DeadActor))
		{
			TowerTurret->HandleDestruction();
			TargetTowers--;
		}

		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerTurretCount();
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerTurretCount()
{
	TArray<AActor*> TowerTurretsArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATowerTurret::StaticClass(), TowerTurretsArray);

	return TowerTurretsArray.Num();
}
