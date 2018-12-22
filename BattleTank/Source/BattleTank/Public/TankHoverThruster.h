// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "TankHoverThruster.generated.h"

class UStaticMeshComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankHoverThruster : public USceneComponent
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

public:

	UTankHoverThruster();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Hover();

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float DesiredHeight = 80.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float Gain = 2.4f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	float Damping = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hover")
	int32 NumberOfThrusters = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float CutoffAngularVelocity = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float CutoffRollVelocity = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Cutoff")
	float RestartTime = 2.f;

	//UPROPERTY(EditDefaultsOnly, Category = Cutoff)
	//float StartupTime = 1.f;

private:
	float Mass;

	float Weight; // This is the weight to be supported by each individual thruster; i.e. inversely proportional to NumberOfThrusters

	UPrimitiveComponent* TankRoot = nullptr;
	UPrimitiveComponent* TankLeg = nullptr;

	float GetHeight(FVector ThrustPoint);
	float LastHeight;
	float CutoffTime = 0;
};
