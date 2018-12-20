// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

 // Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankGearHead;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet); // Get the barrel via the blueprint hook, called on BeginPlay

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet); // Get the turret via the blueprint hook, called on BeginPlay

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetGearHeadReference(UTankGearHead* GearHeadToSet); // Get the gearhead via the blueprint hook, called on BeginPlay


	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();


	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	void AimAt(FVector HitLocation);

private:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Called to bind functionality to input

	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;
	UTankGearHead* GearHead = nullptr;

	float LastFireTime = 0;
};
