// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ToonTanksGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage >= 0.0f)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
		HandleDeath(DamagedActor);

	}
}

void UHealthComponent::HandleDeath(AActor* DeadActor) const
{
	if (CurrentHealth <= 0.0f)
	{
		if (AToonTanksGameMode* ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			ToonTanksGameMode->ActorDied(DeadActor);
		}
	}
}