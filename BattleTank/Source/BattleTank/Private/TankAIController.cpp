// Copyright ChristmasLights 2018

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(ControlledTank)) { return; }

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(PlayerTank)) { return; }
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