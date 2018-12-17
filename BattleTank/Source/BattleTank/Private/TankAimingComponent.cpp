// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)  // AIMING CHAIN 04 (called from Tank). Performs ballistic calculation given desired location and tank launch speed.
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));



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
		false);

	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // Turn OutLaunchVelocity into unit vector
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // Tells us the P/Y/R of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector AimedLocation = StartLocation + BarrelRotator.Vector() * 10000;
	if (!DeltaRotator.Equals(FRotator(0), 0.5))
	{
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			AimedLocation,
			FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			2.f);
	}
	else
	{
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			AimedLocation,
			FColor(0, 255, 0),
			false,
			0.f,
			0.f,
			4.f);
	}
	
	Barrel->Elevate(DeltaRotator.Pitch); // AIMING CHAIN 05, calls to TankBarrel
	Turret->Rotate(DeltaRotator.Yaw); // AIMING CHAIN 05, calls to TankTurret
}