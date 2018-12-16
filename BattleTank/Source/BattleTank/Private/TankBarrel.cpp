// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{

	// Move barrel right amount this frame

	// Given a max elevation speed and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called at %f"), DegreesPerSecond)
}