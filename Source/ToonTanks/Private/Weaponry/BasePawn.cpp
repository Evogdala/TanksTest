// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/Projectile.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;


	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(Capsule);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMeshComponent"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::TowerRotation(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);

	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretRotation, LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), TowerTurningSpeed));
}

void ABasePawn::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (Projectile)
	{
		Projectile->SetOwner(this);
	}
}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

