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

// Holds barrel's properties
UCLASS( ClassGroup=("_TankComponents"), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet); // Uses forward declaration to hook into UTankBarrel class
	void SetTurretReference(UTankTurret* TurretToSet); // Uses forward declaration to hook into UTankTurret class
	void SetGearHeadReference(UTankGearHead* GearHeadToSet); // Uses forward declaration to hook into UTankGearHead class

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UTankGearHead* GearHead = nullptr;

	FColor IndicatorColor = FColor(255, 0, 0);

	bool bValidHit;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveHeadToward(FVector HitLocation);

};
