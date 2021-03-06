// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enumeration for barrel state
UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Reloading,
	Locked,
	OutOfAmmo
};

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this pawn's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankBarrelTurret);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();

	void AimAt(FVector HitLocation);

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 10;

	double LastFireTime = 0;

	FVector AimDirection;

	bool IsBarrelMoving();

	void MoveBarrelTowards(FVector AimDirection);
};
