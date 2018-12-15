// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not posessing a tank!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIcontroller posessing %s!"), *ControlledTank->GetName());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}