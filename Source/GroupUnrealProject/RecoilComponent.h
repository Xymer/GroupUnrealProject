// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPUNREALPROJECT_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()
		
		
public:	
	class APlayerController* Controller;

	URecoilComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float RecoilYaw = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float upRecoilTimer = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float downRecoilTimer = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float recoilDurationMultiplier = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float recoilPitchUpwardsPower = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float recoilPitchDownwardsPower = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float powerMultiplier = 2.0f;

protected:
	virtual void BeginPlay() override;

	bool hasFired = false;
	float currentUpRecoilTimer = 0.0f;
	float currentDownRecoilTimer = 0.0f;
	float recoilDownwardTargetRotation;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddRecoil();
	float RandomizeRecoilYaw(float Value);
	void OnDropWeapon();
		
};
