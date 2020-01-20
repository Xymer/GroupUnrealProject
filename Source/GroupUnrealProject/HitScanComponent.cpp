// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanComponent.h"
#include "GameFramework/Controller.h"
// Sets default values for this component's properties
UHitScanComponent::UHitScanComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitScanComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitScanComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FHitResult UHitScanComponent::LineTrace(FVector StartVector, FVector EndVector)
{

	GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector * HitScanRange, ECC_Visibility);
	
	DrawDebugLine(GetWorld(), StartVector, EndVector * HitScanRange, FColor::Green, false, 5.0f);
	return HitResult;
	
	
}

