// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankGearHead.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankGearHead : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Aim(float RelativePitchSpeed, float RelativeYawSpeed);

private:

	UPROPERTY(EditDefaultsOnly)
	float MaxPitchDegreesPerSecond = 180.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxYawDegreesPerSecond = 180.f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxPitch = 45.f;

	UPROPERTY(EditDefaultsOnly)
	float MinPitch = -5.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxYaw = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float MinYaw = -120.f;

};
