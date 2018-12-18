// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{

	// Move turret right amount this frame

	// Given a max turn speed and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Yaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, Yaw, 0));

}
