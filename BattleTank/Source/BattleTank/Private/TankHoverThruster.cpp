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
	if (!ensure(TankRoot)) { return; }

	TankLeg = Cast<UPrimitiveComponent>(GetAttachParent());
	if (!ensure(TankLeg)) { return; }

	Mass = TankRoot->GetMass() / NumberOfThrusters;

	Weight = -1 * Mass * GetWorld()->GetGravityZ();

	LastGoodHeight = DesiredHeight;

	Status = EHoverState::Abort;
}

void UTankHoverThruster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Hover();
}

void UTankHoverThruster::Hover()
{
	FVector ThrustPoint = GetAttachParent()->GetSocketLocation(FName("HoverThruster")); // Gets thruster location in world

	float Height = GetHeight(ThrustPoint);
	float Time = GetWorld()->GetTimeSeconds();

	FVector AngVel = TankLeg->GetPhysicsAngularVelocityInDegrees();
	FVector LinVel = TankLeg->GetPhysicsLinearVelocityAtPoint(ThrustPoint);

	Status = HoverState(Height, Time, AngVel.Size());

	switch (Status)
	{
	case EHoverState::Cutoff: { return; }
	case EHoverState::Abort: { CutoffTime = Time; return; }
	case EHoverState::Starting:
		{
			float Accel = ((DesiredHeight - Height) * Gain * Gain * Gain * Gain * Gain) - (LinVel.Z * Damping * Gain * 2);
			float Force = (Mass * Accel) * (Time - CutoffTime - RestartTime) * (Time - CutoffTime - RestartTime) + Weight;
			TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
			return;
		}
	case EHoverState::Hovering:
		{
			LastGoodHeight = Height;
			float Accel = ((DesiredHeight - Height) * Gain * Gain * Gain * Gain * Gain) - (LinVel.Z * Damping * Gain * 2);
			float Force = (Mass * Accel) + Weight;
			TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
			return;
		}
	case EHoverState::Gliding:
		{
			float Accel = ((DesiredHeight - LastGoodHeight) * Gain * Gain * Gain * Gain * Gain) - (LinVel.Z * Damping * Gain * 2);
			float Force = (Mass * Accel) + Weight;
			TankRoot->AddForceAtLocation(Force*(TankLeg->GetUpVector()), ThrustPoint);
			return;
		}
	}
}

// Get the current state of the vehicle
EHoverState UTankHoverThruster::HoverState(float Height, float Time, float AngVel) const
{
	if (Time - CutoffTime > RestartTime) // If the thruster has cooled off
	{
		if (Height < CutoffHeight && AngVel < CutoffAngularVelocity) // If the vehicle isn't too high or spinning too fast
		{
			if (Time - CutoffTime - RestartTime > 1) // If 1-second ramp-up has completed
			{
				if (Height < GlideHeight) { return EHoverState::Hovering; } // If the thruster is below the gliding zone

				else { return EHoverState::Gliding; } // Since it isn't too high and isn't below the gliding zone, it must be in the gliding zone
			}
			else { return EHoverState::Starting; } // The thruster is in the first second of ramping up
		}
		else { return EHoverState::Abort; } // Vehicle is too high or spinning too fast -- abort!
	}
	else { return EHoverState::Cutoff; } // The thruster has not yet cooled off.
}

//Line trace by visibility from hover thruster socket point down
float UTankHoverThruster::GetHeight(FVector ThrustPoint) const
{
	FHitResult Ground;
	GetWorld()->LineTraceSingleByChannel(Ground, ThrustPoint, ThrustPoint - FVector(0, 0, DesiredHeight * 100), ECollisionChannel::ECC_Visibility);

	if (Ground.IsValidBlockingHit()) 
	{ return Ground.Distance; }
	else { return 0; } // TODO Get a better behavior for this return value.
}