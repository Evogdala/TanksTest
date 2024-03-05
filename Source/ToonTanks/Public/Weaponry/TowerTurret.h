// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weaponry/BasePawn.h"
#include "TowerTurret.generated.h"

class ATank;

UCLASS()
class TOONTANKS_API ATowerTurret : public ABasePawn
{
	GENERATED_BODY()
	

public:
	virtual void Tick(float DeltaTime) override;

	bool IsEnemyInRange();

	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (ClampMin = 1.0))
	double FireRange = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (ClampMin = 1.0))
	float FireRate = 2.0f;

	FTimerHandle FireRateTimerHandle;
	
	void CheckFireCondition();
};
