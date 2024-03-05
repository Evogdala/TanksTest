// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TanksHUD.h"
#include "Blueprint/UserWidget.h"

void ATanksHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

	for (UUserWidget* WidgetsPair : Widgets)
	{
		UUserWidget* Widget = WidgetsPair;
		if (!Widget) continue;
		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}
