// Copyright ChristmasLights 2018

#include "../Public/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{

	// Move barrel right amount this frame

	// Given a max elevation speed and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));

}
