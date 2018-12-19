// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditDefaultsOnly, Category = Hover)
		float DesiredHeight = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
		float Gain = 6.f;

	UPROPERTY(EditDefaultsOnly, Category = Hover)
		float Damping = 1.f;

private:
	float Mass;

	float Weight;

	UPrimitiveComponent* TankRoot;
	UPrimitiveComponent* TankLeg;

	float GetHeight(FVector ThrustPoint);
	float LastHeight = 0;
};
