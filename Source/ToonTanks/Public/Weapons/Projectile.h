// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UPhysicalMaterial;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* SmokeTrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (ClampMin = 1.0))
	float Damage = 15.0f;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TMap<UPhysicalMaterial*, UParticleSystem*> EffectsMap;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, Category = "VFX")
	FVector ImpactHoleSize = FVector(20.0f);

	UPROPERTY(EditAnywhere, Category = "VFX")
	float ImpactHoleLifeSpan = 3.0f;

	UPROPERTY(EditAnywhere, Category = "VFX")
	float ImpactHoleFadeOutTime = 0.7f;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Sound Effects")
	USoundBase* HitSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void SpawnVFX(const FHitResult& Hit);
};
