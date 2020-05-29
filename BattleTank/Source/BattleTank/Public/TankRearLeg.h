// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankRearLeg.generated.h"

UCLASS(ClassGroup = ("_TankComponents"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankRearLeg : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UTankRearLeg();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	void ApplyThrust();

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ThrusterMaxForce = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float CutoffHeight = 6000.f;

private:
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	float GetHeight() const;

	FVector ThrustPoint;

	float CurrentThrottle = 0;
};
