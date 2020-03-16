// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilComponent.h"
#include "GameFramework/PlayerController.h"

URecoilComponent::URecoilComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bool getNewController = true;
}

void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Controller != nullptr) {
		if (hasFired == true) {
			if (currentUpRecoilTimer <= upRecoilTimer && currentUpRecoilTimer >= 0) {
				currentUpRecoilTimer -= DeltaTime * recoilDurationMultiplier; // Upwards recoil
				Controller->AddPitchInput(-currentUpRecoilTimer * recoilPitchUpwardsPower); //Pitch increases faster early on in the timer
			}
			else if (currentDownRecoilTimer <= downRecoilTimer && currentDownRecoilTimer >= 0) {
				if (((Controller->GetControlRotation().Pitch) > recoilDownwardTargetRotation) || 
					((Controller->GetControlRotation().Pitch) > 0 && recoilDownwardTargetRotation > 270)) {
					if (FMath::IsWithin(recoilDownwardTargetRotation, 0.0f, 90.0f) && // Check if target rotation is in a place where we want downward recoil
							FMath::IsWithin(Controller->GetControlRotation().Pitch, 0.0f, 90.0f) ||
								FMath::IsWithin(recoilDownwardTargetRotation, 270.0f, 360.0f) &&
									FMath::IsWithin(Controller->GetControlRotation().Pitch, 270.0f, 360.0f) || 
										FMath::IsWithin(Controller->GetControlRotation().Pitch, 0.0f, 90.0f)) { //If rotation goes below 0 into 360, still move recoil toward downwards target.
						currentDownRecoilTimer -= DeltaTime * recoilDurationMultiplier; // Downwards recoil
						Controller->AddPitchInput(currentDownRecoilTimer * recoilPitchDownwardsPower); //Pitch decreases faster early on in the timer
						if (currentDownRecoilTimer <= 0) { 
							if (FMath::IsWithin(Controller->GetControlRotation().Pitch, recoilDownwardTargetRotation - 0.2f, recoilDownwardTargetRotation + 0.2f) || // If controller is in place where downward recoil should be stopped
								(FMath::IsWithin(Controller->GetControlRotation().Pitch, 0.0f, 90.0f) && Controller->GetControlRotation().Pitch < recoilDownwardTargetRotation) ||
								(FMath::IsWithin(Controller->GetControlRotation().Pitch, 270.0f, 360.0f) && (FMath::IsWithin(recoilDownwardTargetRotation, 0.0f, 90.0f))) ||
								FMath::IsWithin(Controller->GetControlRotation().Pitch, 270.0f, 360.0f) && ((Controller->GetControlRotation().Pitch < recoilDownwardTargetRotation) || FMath::IsWithin(recoilDownwardTargetRotation, 0.0f, 90.0f))) {
								hasFired = false;
							}
						}
					}
				}
			}
		}
	}
}

void URecoilComponent::AddRecoil()
{
	recoilDownwardTargetRotation = Controller->GetControlRotation().Pitch;

	Controller->AddYawInput(RandomizeRecoilYaw(RecoilYaw * 0.01));

	hasFired = true;

	currentUpRecoilTimer = upRecoilTimer; // Reset powers every time gun is fired
	currentDownRecoilTimer = downRecoilTimer;
}

float URecoilComponent::RandomizeRecoilYaw(float Value)
{
	return FMath::RandRange(-Value, Value);
}

void URecoilComponent::OnDropWeapon()
{
	Controller = nullptr;
}