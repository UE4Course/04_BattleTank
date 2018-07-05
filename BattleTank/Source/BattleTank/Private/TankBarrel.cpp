// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"
#include "Engine/Engine.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Calculate the new elevation for the given frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// Clamps the elevation to min or max elevation degree
	RawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegree, MaxElevationDegree);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}
