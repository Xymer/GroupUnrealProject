// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScan.h"

// Sets default values for this component's properties
UHitScan::UHitScan()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitScan::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitScan::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

