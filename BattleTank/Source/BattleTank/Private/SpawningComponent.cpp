// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawningComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "SprungWheel.h"


// Sets default values for this component's properties
USpawningComponent::USpawningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpawningComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());

	if (!SpawnedActor) { return; }
	auto Parent = GetAttachParent();
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

