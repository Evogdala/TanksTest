// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weaponry/BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputMappingContext* TankMappingContext;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 1.0))
	double TankVelocity = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 1.0))
	double TankTurnRate = 200.0f;

	UPROPERTY()
	APlayerController* TankPlayerController;

	void AddMappingContext();
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

	bool bAlive = true;

public:
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	bool IsTankAlive() const { return bAlive; }
};
