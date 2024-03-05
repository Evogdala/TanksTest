// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/TowerTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Weaponry/Tank.h"

void ATowerTurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATowerTurret::CheckFireCondition, FireRate, true);
}

void ATowerTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEnemyInRange())
	{
		TowerRotation(Tank->GetActorLocation());
	}
}

bool ATowerTurret::IsEnemyInRange()
{
	if (Tank)
	{
		double Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}
	return false;
}

void ATowerTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATowerTurret::CheckFireCondition()
{
	if (!Tank) return;

	if (IsEnemyInRange() && Tank->IsTankAlive())
	{
		Fire();
	}
}
