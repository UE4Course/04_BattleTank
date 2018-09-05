// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }

	// Ray Cast from crosshair
	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }

		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector CameraWorldLocation, CameraWorldDirection;

	// Find the viewport size
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Find the crosshair position Start
	// and the direction End
	DeprojectScreenPositionToWorld(
		CrosshairXLocation * ViewportSizeX,
		CrosshairYLocation * ViewportSizeY,
		CameraWorldLocation,
		CameraWorldDirection
	);

	// Line trace along the direction
	return GetAimHitLocation(CameraWorldDirection, OutHitLocation);
}

bool ATankPlayerController::GetAimHitLocation(FVector AimDirection, FVector & OutHitLocation) const
{
	FHitResult AimHit;
	FVector CameraWorldLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = CameraWorldLocation + (AimDirection * LineTraceRange);

	// Line trace along the direction
	if (GetWorld()->LineTraceSingleByChannel(
			AimHit,
			CameraWorldLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		// If we hit something, sets the out location
		// of the impact point and returns true
		OutHitLocation = AimHit.ImpactPoint;
		return true;
	}
	else
	{
		OutHitLocation = FVector(0);
		return false;
	}
}

