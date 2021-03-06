// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = ("_TankComponents"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward movement, +1 is max updward movement
	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 25.f;

};
