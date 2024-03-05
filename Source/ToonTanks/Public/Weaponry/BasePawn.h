// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class AProjectile;
class UHealthComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction();

protected:
	virtual void BeginPlay() override;


	void TowerRotation(FVector LookAtTarget);
	void Fire();
private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 1.0))
	float TowerTurningSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;
};
