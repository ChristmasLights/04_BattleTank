// Copyright ChristmasLights 2018

#include "../Public/TankMovementComponent.h"
#include "../Public/TankRearLeg.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::Initialize(UTankRearLeg * LeftRearLegToSet, UTankRearLeg * RightRearLegToSet)
{
	LeftRearLeg = LeftRearLegToSet;
	RightRearLeg = RightRearLegToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super::, as we are replacing the functionality here

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
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