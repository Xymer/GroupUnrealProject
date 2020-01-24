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
	// Sets default values for this component's properties
	class APlayerController* Controller;
	URecoilComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Recoil")
	float RecoilPitch = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float RecoilYaw = 3.0f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddRecoil();
	float RandomizeRecoil(float Value);
	void OnDropWeapon();
		
};
