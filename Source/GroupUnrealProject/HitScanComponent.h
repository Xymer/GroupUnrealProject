// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "HitScanComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPUNREALPROJECT_API UHitScanComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitScanComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Scan")
		float HitScanRange = 5000;
	

private:
	FHitResult HitResult;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FHitResult LineTrace(FVector StartVector,FVector EndVector);

		
};
