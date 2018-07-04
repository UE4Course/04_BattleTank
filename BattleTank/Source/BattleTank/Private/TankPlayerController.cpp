// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	ATank* Tank = GetControlledTank();

	if (Tank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing Tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s found!"), *(Tank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Ray Cast from crosshair
	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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

