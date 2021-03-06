// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

// Forward declarations
class ASprungWheel;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

private:
	// Constructor
	UTankTrack();

	TArray<class ASprungWheel *> GetWheels() const;

	void DriveTrack(float CurrentThrottle);

	// Max Force apply to one track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 300000;
};
