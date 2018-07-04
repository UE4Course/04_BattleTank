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
		// UE_LOG(LogTemp, Warning, TEXT("There is a Hit at poition : %s"), *(HitLocation.ToString()));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector Start, End;
	FHitResult AimHit;

	// Find the viewport size
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Find the crosshair position Start
	// and the direction End
	DeprojectScreenPositionToWorld(
		CrosshairXLocation * ViewportSizeX,
		CrosshairYLocation * ViewportSizeY,
		Start,
		End
	);

	// Line trace along the direction
	if(GetWorld()->LineTraceSingleByObjectType(
		AimHit,
		Start,
		End * MaximumRange,
		FCollisionObjectQueryParams(),
		FCollisionQueryParams()
	))
	{
		// If we hit something, sets the out location
		// of the impact point and returns true
		OutHitLocation = AimHit.ImpactPoint;
		return true;
	}
	else
	{
		return false;
	}
}

