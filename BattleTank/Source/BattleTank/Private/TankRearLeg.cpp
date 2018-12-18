// Fill out your copyright notice in the Description page of Project Settings.

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

	TankRoot->AddForceAtLocation(ForceApplied, ThrustPoint);
}
