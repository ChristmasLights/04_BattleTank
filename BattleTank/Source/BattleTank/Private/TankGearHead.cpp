// Copyright ChristmasLights 2018

#include "TankGearHead.h"
#include "../Public/Tank.h"

void UTankGearHead::Aim(float RelativePitchSpeed, float RelativeYawSpeed)
{
	RelativePitchSpeed = FMath::Clamp<float>(RelativePitchSpeed, -1, 1);
	auto PitchChange = RelativePitchSpeed * MaxPitchDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewPitch = RelativeRotation.Pitch + PitchChange;
	auto Pitch = FMath::Clamp<float>(RawNewPitch, MinPitch, MaxPitch);

	RelativeYawSpeed = FMath::Clamp<float>(RelativeYawSpeed, -1, 1);
	auto YawChange = RelativeYawSpeed * MaxYawDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewYaw = RelativeRotation.Yaw + YawChange;
	auto Yaw = FMath::Clamp<float>(RawNewYaw, MinYaw, MaxYaw);

	SetRelativeRotation(FRotator(Pitch, Yaw, 0));
}