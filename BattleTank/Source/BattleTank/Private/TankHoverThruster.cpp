// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankHoverThruster.h"
#include "Components/StaticMeshComponent.h"

UTankHoverThruster::UTankHoverThruster()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankHoverThruster::BeginPlay()
{
	Super::BeginPlay();

	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankLeg = Cast<UPrimitiveComponent>(GetAttachParent());

	/// UE_LOG(LogTemp, Warning, TEXT("Root is %s, leg is %s!"), *TankRoot->GetName(), *TankLeg->GetName())

	Mass = TankRoot->GetMass() / 4;

	Weight = -1 * Mass * GetWorld()->GetGravityZ();
}

void UTankHoverThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Hover();
}

void UTankHoverThruster::Hover()
{
	FVector ThrustPoint = GetAttachParent()->GetSocketLocation(FName("HoverThruster")); // Gets thruster location in world

	/// UE_LOG(LogTemp, Warning, TEXT("Thrust of %f at %s!"), Weight, *ThrustPoint.ToString())

	// Current Height is difference between trace hit point and socket z point
	// Height Deviation is difference between Current Height and Desired Float Height
	// Raw Accel is Height Deviation times(Gain squared)
	// Socket Z Speed is Physics Linear Velocity z component from socket
	// Accel Feather is Socket Z Speed times Damping times Gain times 2
	// Accel is Raw Accel minus Accel Feather
	// Force is (Accel times Mass) + Weight


	// TODO Consider false line trace
	float Height = GetHeight(ThrustPoint);
	float ZSpeed = TankLeg->GetPhysicsLinearVelocityAtPoint(ThrustPoint).Z;

	float Accel = ((DesiredHeight - Height) * Gain * Gain) - (ZSpeed * Damping * Gain * 2);

	float Force = (Mass * Accel) + Weight;

	// UE_LOG(LogTemp, Warning, TEXT("Force is %f!"), Force)

	// Add Force at socket
	TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
}

//Line trace by visibility from hover thruster socket point down
float UTankHoverThruster::GetHeight(FVector ThrustPoint)
{
	FHitResult Ground;
	GetWorld()->LineTraceSingleByChannel(Ground, ThrustPoint, ThrustPoint - FVector(0, 0, 1000), ECollisionChannel::ECC_Visibility);

	if (Ground.IsValidBlockingHit())
	{
		LastHeight = Ground.Distance;
		return Ground.Distance;
	}
	else
	{
		return LastHeight;
	}
}
