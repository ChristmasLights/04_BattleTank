// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankRearLeg.h"

void UTankMovementComponent::Initialize(UTankRearLeg * LeftRearLegToSet, UTankRearLeg * RightRearLegToSet)
{
	LeftRearLeg = LeftRearLegToSet;
	RightRearLeg = RightRearLegToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftRearLeg || !RightRearLeg) { UE_LOG(LogTemp, Error, TEXT("No Leg!")); return; }
	LeftRearLeg->SetThrottle(Throw);
	RightRearLeg->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftRearLeg || !RightRearLeg) { UE_LOG(LogTemp, Error, TEXT("No Leg!")); return; }
	LeftRearLeg->SetThrottle(Throw);
	RightRearLeg->SetThrottle(-Throw);
}