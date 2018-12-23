// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "TankHoverThruster.generated.h"


UENUM()
enum class EHoverState : uint8
{
	Abort,
	Cutoff,
	Starting,
	Hovering,
	Gliding
};


class UStaticMeshComponent;

UCLASS(ClassGroup = ("_TankComponents"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankHoverThruster : public USceneComponent
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

	// TODO Wire up cutoff event to tank movement controller -- have it also cut off rear thrusters when too high, so player can't fly away and out of the map.

public:

	UTankHoverThruster();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Hover();

	void SlideDamp(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float DesiredHeight = 140.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float Gain = 2.4f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float Damping = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float GlideHeight = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	int32 NumberOfThrusters = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float CutoffAngularVelocity = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float CutoffHeight = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float RestartTime = 2.f;

	UPROPERTY(BlueprintReadOnly, Category = "Hover")
	EHoverState Status;

private:
	float Mass;

	float Weight; // This is the weight to be supported by each individual thruster; i.e. inversely proportional to NumberOfThrusters

	EHoverState HoverState(float Height, float Time, float AngVel) const;

	UPrimitiveComponent* TankRoot = nullptr;
	UPrimitiveComponent* TankLeg = nullptr;

	float GetHeight(FVector ThrustPoint) const;
	float LastGoodHeight;
	float CutoffTime;
};
