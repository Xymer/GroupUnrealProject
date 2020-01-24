// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URecoilComponent::AddRecoil()
{
	Controller->AddPitchInput(-RecoilPitch);
	Controller->AddYawInput(RandomizeRecoil(RecoilYaw));
}

float URecoilComponent::RandomizeRecoil(float Value)
{
	return FMath::RandRange(-Value, Value);
}

void URecoilComponent::OnDropWeapon()
{
	Controller = nullptr;
}

