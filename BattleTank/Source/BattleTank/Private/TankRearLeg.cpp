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

void UTankRearLeg::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * ThrusterMaxForce;
	ThrustPoint = GetSocketLocation(FName("Thruster"));
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) { return; }

	TankRoot->AddForceAtLocation(ForceApplied, ThrustPoint);
}

void UTankRearLeg::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
}
