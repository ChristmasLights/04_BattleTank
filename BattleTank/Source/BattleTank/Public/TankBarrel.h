// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = ("_TankComponents"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward movement, +1 is max updward movement
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 45.f;

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegrees = -5.f;

};
