// Copyright ChristmasLights 2018

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
// Depends on movement component via pathfinding

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank && ControlledTank && AimingComponent)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// AimingComponent->Fire();
}