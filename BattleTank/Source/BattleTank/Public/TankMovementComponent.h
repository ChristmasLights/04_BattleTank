// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Engine/World.h"
#include "TankMovementComponent.generated.h"

class UTankRearLeg;

UCLASS(ClassGroup = ("_TankComponents"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankRearLeg* LeftRearLegToSet, UTankRearLeg* RightRearLegToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);
	
private:

	UTankRearLeg* LeftRearLeg = nullptr;
	UTankRearLeg* RightRearLeg = nullptr;

	// Called from the pathfinding logic by an AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

};
