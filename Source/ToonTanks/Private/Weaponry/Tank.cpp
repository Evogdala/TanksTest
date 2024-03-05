// Fill out your copyright notice in the Description page of Project Settings.


#include "Weaponry/Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	AddMappingContext();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult CursorHit;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, 
			false, 
			CursorHit);
		if (CursorHit.bBlockingHit)
		{
			TowerRotation(CursorHit.ImpactPoint);
		}
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		PlayerEnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);
		PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::AddMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TankMappingContext, 0);
		}
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const double DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	const double Speed = DeltaSeconds * TankVelocity;

	const FVector DeltaLocation = FVector(1.0f, 0.0f, 0.0f);
	AddActorLocalOffset(DeltaLocation * MovementVector.Y * Speed, true);
}

void ATank::Turn(const FInputActionValue& Value)
{
	const FVector2D TurnVector = Value.Get<FVector2D>();

	const double DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	const double TurnSpeed = DeltaSeconds * TankTurnRate;

	const FRotator YawRotation = FRotator(0.0f, 1.0f, 0.0f);
	AddActorLocalRotation(YawRotation * TurnVector.X * TurnSpeed, true);
}
