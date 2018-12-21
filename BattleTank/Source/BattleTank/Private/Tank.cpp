// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankMovementComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed); // AIMING CHAIN 03 (called from Controller to AimingComponent). Here is where we add the launch speed variable.
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet); // Once called via the blueprint on BeginPlay, passes the barrel through to the aiming component

	Barrel = BarrelToSet; // Need this for spawning the projectile
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet); // Once called via the blueprint on BeginPlay, passes the turret through to the aiming component
}

void ATank::SetGearHeadReference(UTankGearHead* GearHeadToSet)
{
	TankAimingComponent->SetGearHeadReference(GearHeadToSet); // Once called via the blueprint on BeginPlay, passes the gearhead through to the aiming component
}

void ATank::Fire()
{
	bool bIsReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}	
}
