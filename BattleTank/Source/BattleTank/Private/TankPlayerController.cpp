// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"


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
		UE_LOG(LogTemp, Warning, TEXT("There is a Hit at poition : %s"), *(HitLocation.ToString()));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	FHitResult AimHit;
	FVector Start;
	FVector End;

	DeprojectScreenPositionToWorld(0.5f, 0.33f, Start, End);

	End = End * 100000;

	bool HitSomething = GetWorld()->LineTraceSingleByObjectType(
		AimHit,
		Start,
		End,
		FCollisionObjectQueryParams(),
		FCollisionQueryParams()
		);

	OutHitLocation = AimHit.ImpactPoint;

	return HitSomething;
}

