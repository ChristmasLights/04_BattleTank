// Copyright ChristmasLights 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);
};
