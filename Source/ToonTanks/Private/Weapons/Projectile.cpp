// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/DecalComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	SetRootComponent(BaseMesh);
	BaseMesh->bReturnMaterialOnMove = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1200.0f;
	ProjectileMovementComponent->MaxSpeed = 1600.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	SmokeTrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	SmokeTrailParticles->SetupAttachment(GetRootComponent());
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetOwner())
	{
		Destroy();
		return;
	}

	AController* OwnerInstigator = GetOwner()->GetInstigatorController();
	if (!OwnerInstigator) return;

	if (OtherActor && OtherActor != GetOwner() && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, UDamageType::StaticClass());

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.ImpactPoint);
		}

		SpawnVFX(Hit);
	}

	Destroy();
}

void AProjectile::SpawnVFX(const FHitResult& Hit)
{
	auto Effect = HitParticles;

	if (Hit.PhysMaterial.IsValid())
	{
		const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Effect, GetActorLocation(), GetActorRotation());

	if (Material)
	{
		UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			Material,
			ImpactHoleSize,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation()
		);

		if (DecalComponent)
		{
			DecalComponent->SetFadeOut(ImpactHoleLifeSpan, ImpactHoleFadeOutTime);
		}
	}

	if (HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
}



