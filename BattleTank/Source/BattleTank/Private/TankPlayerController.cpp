// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	ATank* Tank = GetControlledTank();

	if (Tank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing Tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s found!"), *(Tank->GetName()));
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

