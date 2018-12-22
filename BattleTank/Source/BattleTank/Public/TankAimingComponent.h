// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel; 
class UTankTurret;
class UTankGearHead;


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
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet, UTankGearHead* GearHeadToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UTankGearHead* GearHead = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveHeadToward(FVector HitLocation);

};
