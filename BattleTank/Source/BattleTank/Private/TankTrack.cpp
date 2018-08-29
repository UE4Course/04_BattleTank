// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *GetName(), Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
	auto Location = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, Location);
}


