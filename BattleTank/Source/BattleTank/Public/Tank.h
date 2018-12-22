// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

 // Forward declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	ATank();

	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr; // TODO remove

	float LastFireTime = 0;
};
