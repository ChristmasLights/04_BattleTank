// Copyright ChristmasLights 2018

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/TankGearHead.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet, UTankGearHead * GearHeadToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	GearHead = GearHeadToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

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
	MoveHeadToward(HitLocation);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	
	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); // Tells us the P/Y/R of the barrel at the moment
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::MoveHeadToward(FVector HitLocation)
{
	if (!ensure(GearHead)) { return; }

	FVector StartLocation = GearHead->GetSocketLocation(FName("Eye"));
	FHitResult AimLocation;
	GetWorld()->LineTraceSingleByChannel(
		AimLocation,
		StartLocation,
		((GearHead->GetForwardVector() * 100000) + StartLocation),
		ECollisionChannel::ECC_Visibility);

	auto GearHeadRotator = GearHead->GetForwardVector().Rotation();
	auto LookRotator = (HitLocation - StartLocation).Rotation();
	auto DeltaRotator = LookRotator - GearHeadRotator;

	GearHead->Aim(DeltaRotator.Pitch, DeltaRotator.Yaw);
}