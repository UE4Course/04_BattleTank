// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"


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

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
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

void ATankAIController::AimTowardsPlayer()
{
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}