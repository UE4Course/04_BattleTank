// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	// Logout AI Tank
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing Tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s found!"), *(ControlledTank->GetName()));
	}

	// Logout Player Tank
	if (PlayerTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing Target Player Tank!"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank %s was found!"), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* TPC = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	return TPC->GetControlledTank();
}