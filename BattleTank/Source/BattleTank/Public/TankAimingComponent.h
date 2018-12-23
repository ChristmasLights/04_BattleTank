// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel; 
class UTankTurret;
class UTankGearHead;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=("_TankComponents"), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet, UTankGearHead* GearHeadToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);
	void MoveHeadToward(FVector HitLocation);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UTankGearHead* GearHead = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 0.1f;

	float LastFireTime = 0;
};
