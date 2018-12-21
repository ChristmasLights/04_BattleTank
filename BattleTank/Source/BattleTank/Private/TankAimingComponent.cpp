// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/TankGearHead.h"
// #include "DrawDebugHelpers.h"

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
		bValidHit = true;
	}
	else
	{
		bValidHit = false;
	}
	MoveHeadToward(HitLocation);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	Turret = TurretToSet;
}

void UTankAimingComponent::SetGearHeadReference(UTankGearHead* GearHeadToSet) // Passed from the Tank, set up via the blueprint on BeginPlay
{
	GearHead = GearHeadToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // Tells us the P/Y/R of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (!DeltaRotator.Equals(FRotator(0), 0.5))
	{
		IndicatorColor = FColor(255, 0, 0);
	}
	else
	{
		IndicatorColor = FColor(0, 125, 250);
	}
	
	Barrel->Elevate(DeltaRotator.Pitch); // AIMING CHAIN 05, calls to TankBarrel
	Turret->Rotate(DeltaRotator.Yaw); // AIMING CHAIN 05, calls to TankTurret
}

void UTankAimingComponent::MoveHeadToward(FVector HitLocation)
{
	if (!GearHead) { return; }

	FVector StartLocation = GearHead->GetSocketLocation(FName("Eye"));
	FHitResult AimLocation;
	GetWorld()->LineTraceSingleByChannel(
		AimLocation,
		StartLocation,
		((GearHead->GetForwardVector() * 100000) + StartLocation),
		ECollisionChannel::ECC_Visibility);
	
	/*
	if (bValidHit) {
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			AimLocation.Location,
			IndicatorColor,
			false,
			0.f,
			0.f,
			2.f);
	}
	*/

	auto GearHeadRotator = GearHead->GetForwardVector().Rotation();
	auto LookRotator = (HitLocation - StartLocation).Rotation();
	auto DeltaRotator = LookRotator - GearHeadRotator;

	GearHead->Aim(DeltaRotator.Pitch, DeltaRotator.Yaw);
}