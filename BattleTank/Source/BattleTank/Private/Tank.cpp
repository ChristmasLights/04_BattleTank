// Copyright ChristmasLights 2018

#include "../Public/Tank.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Need super for Blueprint BeginPlay to trigger
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
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
