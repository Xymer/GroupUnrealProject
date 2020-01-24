// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoomComponent.h"
#include "Math/UnrealMathVectorCommon.h"

// Sets default values for this component's properties
UZoomComponent::UZoomComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UZoomComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UZoomComponent::ZoomIn()
{
	CameraComponent->SetFieldOfView(ZoomValue);
}

void UZoomComponent::ZoomOut()
{
	CameraComponent->SetFieldOfView(DefaultZoomValue);
}

/*
* When dropping weapon zoom out to default value and CameraComponent to nullptr
*/
void UZoomComponent::ZoomOutOnDropWeapon()
{
	CameraComponent->SetFieldOfView(DefaultZoomValue);
	CameraComponent = nullptr;
}

