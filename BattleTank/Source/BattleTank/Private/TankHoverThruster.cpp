// Copyright ChristmasLights 2018

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
	if (TankRoot == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Couldn't find Leg attach parent!")); return; }

	TankLeg = Cast<UPrimitiveComponent>(GetAttachParent());
	if (TankRoot == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Couldn't find HoverThruster attach parent!")); return; }

	Mass = TankRoot->GetMass() / NumberOfThrusters;

	Weight = -1 * Mass * GetWorld()->GetGravityZ();

	LastHeight = DesiredHeight;
}

void UTankHoverThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Hover();
}

void UTankHoverThruster::Hover()
{
	FVector ThrustPoint = GetAttachParent()->GetSocketLocation(FName("HoverThruster")); // Gets thruster location in world

	// Current Height is difference between trace hit point and socket z point
	// Height Deviation is difference between Current Height and Desired Float Height
	// Raw Accel is Height Deviation times(Gain squared)
	// Socket Z Speed is Physics Linear Velocity z component from socket
	// Accel Feather is Socket Z Speed times Damping times Gain times 2
	// Accel is Raw Accel minus Accel Feather
	// Force is (Accel times Mass) + Weight


	float Height = GetHeight(ThrustPoint);

	FVector AngVel = TankLeg->GetPhysicsAngularVelocityInDegrees();
	FVector LinVel = TankLeg->GetPhysicsLinearVelocityAtPoint(ThrustPoint);
	FVector TankAngVel = TankRoot->GetPhysicsAngularVelocityInDegrees();

	float Time = GetWorld()->GetTimeSeconds();

	if (Time - CutoffTime > RestartTime) // If the thruster has cooled off
	{
		if (Height < 1000 && AngVel.Size() < CutoffAngularVelocity) // If the vehicle isn't too high or spinning too fast
		{
			float Accel = ((DesiredHeight - Height) * Gain * Gain * Gain * Gain * Gain) - (LinVel.Z * Damping * Gain * 2);

			if (Time - CutoffTime - RestartTime > 1) // If 1-second ramp-up has completed
			{
				// Calculate and apply proper hover force
				float Force = (Mass * Accel) + Weight;
				TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
			}
			else
			{
				// Ramp up force over 1 second
				float Force = (Mass * Accel) * (Time - CutoffTime - RestartTime) * (Time - CutoffTime - RestartTime) + Weight;
				TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
			}
		}
		else
		{
			CutoffTime = Time;
		}
	}
}

//Line trace by visibility from hover thruster socket point down
float UTankHoverThruster::GetHeight(FVector ThrustPoint)
{
	FHitResult Ground;
	GetWorld()->LineTraceSingleByChannel(Ground, ThrustPoint, ThrustPoint - FVector(0, 0, DesiredHeight * 100000), ECollisionChannel::ECC_Visibility);

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
