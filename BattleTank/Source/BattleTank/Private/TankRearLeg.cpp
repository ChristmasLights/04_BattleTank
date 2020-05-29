// Copyright ChristmasLights 2018

#include "../Public/TankRearLeg.h"


void UTankRearLeg::BeginPlay()
{
	Super::BeginPlay();
}

UTankRearLeg::UTankRearLeg()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankRearLeg::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	ThrustPoint = GetSocketLocation(FName("Thruster"));

	float Height = GetHeight();

	if (Height < CutoffHeight)
	{
		ApplyThrust();
	}
	CurrentThrottle = 0;
}

float UTankRearLeg::GetHeight() const
{
	FHitResult Ground;
	GetWorld()->LineTraceSingleByChannel(Ground, ThrustPoint, ThrustPoint - FVector(0, 0, CutoffHeight), ECollisionChannel::ECC_Visibility); // Needs to ray-cast down REALLY far to ensure hit with ground in flyaway scenario

	if (Ground.IsValidBlockingHit())
	{ 
		return Ground.Distance; 
	}
	else
	{ 
		return CutoffHeight; 
	}
}

void UTankRearLeg::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankRearLeg::ApplyThrust()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * ThrusterMaxForce;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ThrustPoint);
}
