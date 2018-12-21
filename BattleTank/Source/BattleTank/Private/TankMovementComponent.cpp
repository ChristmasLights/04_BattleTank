// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankMovementComponent.h"
#include "../Public/TankRearLeg.h"

void UTankMovementComponent::Initialize(UTankRearLeg * LeftRearLegToSet, UTankRearLeg * RightRearLegToSet)
{
	LeftRearLeg = LeftRearLegToSet;
	RightRearLeg = RightRearLegToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super::, as we are replacing the functionality here

	auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s vectoring to %s"), *TankName, *MoveVelocityString)
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