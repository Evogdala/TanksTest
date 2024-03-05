// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TanksHUD.generated.h"

UCLASS()
class TOONTANKS_API ATanksHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

private:
	UPROPERTY()
	TArray<UUserWidget*> Widgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

};
