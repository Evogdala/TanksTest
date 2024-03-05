// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

class UInputAction;

UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetPlayerEnabledState(bool bPlayerEnabled);

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* PauseAction;

	void OnPauseGame();
};
