// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // TODO does this need to tick?
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)  // AIMING CHAIN 04 (called from Tank). Performs ballistic calculation given desired location and tank launch speed.
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	DrawDebugLine(
		GetWorld(),
		StartLocation,
		HitLocation,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		1.f);

	// Calculate OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor *>(),
		true);

	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // Turn OutLaunchVelocity into unit vector
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Aiming!"), Time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f: No solution found!"), Time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // Tells us the P/Y/R of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); // AIMING CHAIN 05, calls to TankBarrel
}
