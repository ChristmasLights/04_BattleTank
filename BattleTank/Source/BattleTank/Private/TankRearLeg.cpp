// Copyright ChristmasLights 2018

#include "../Public/TankRearLeg.h"


void UTankRearLeg::BeginPlay()
{
	Super::BeginPlay();
}

void UTankRearLeg::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * ThrusterMaxForce;
	ThrustPoint = GetSocketLocation(FName("Thruster"));
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ThrustPoint);
}
