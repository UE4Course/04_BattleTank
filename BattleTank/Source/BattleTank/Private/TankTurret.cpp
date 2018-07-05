// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/Engine.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Calculate the new elevation for the given frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto AzimuthRotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewAzimuthRotation = RelativeRotation.Yaw + AzimuthRotationChange;

	// Clamps the elevation to min or max elevation degree
	//RawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegree, MaxElevationDegree);

	SetRelativeRotation(FRotator(0, RawNewAzimuthRotation, 0));
}


