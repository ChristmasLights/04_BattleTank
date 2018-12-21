// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not posessing a tank!"));
	}

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank!"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Start aiming toward the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	// ControlledTank->Fire();
}