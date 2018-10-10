// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawningComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * MaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	// Apply force on each wheel
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel *> UTankTrack::GetWheels() const
{
	TArray<class USceneComponent*> Children;
	TArray<class ASprungWheel*> Wheels;
	
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		USpawningComponent* SpawningComp = Cast<USpawningComponent>(Child);

		if (!SpawningComp) { continue; }

		ASprungWheel* Wheel = Cast<ASprungWheel>(SpawningComp->GetSpawnedActor());

		if (!Wheel) { continue; }

		Wheels.Add(Wheel);
	}

	return Wheels;
}


