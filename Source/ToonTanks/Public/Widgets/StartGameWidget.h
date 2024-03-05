// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameWidget.generated.h"

UCLASS()
class TOONTANKS_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(BlueprintReadWrite)
	float Countdown;
};
