// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float AcceptanceRadius = 3000; // How close can the AI tank get
};