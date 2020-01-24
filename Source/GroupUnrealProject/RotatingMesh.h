// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagableInterface.h"
#include "Engine/StaticMeshActor.h"
#include "RotatingMesh.generated.h"

/**
 * 
 */
UCLASS()
class GROUPUNREALPROJECT_API ARotatingMesh : public AStaticMeshActor, public IDamagableInterface
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Movement")
		FRotator RotationPerSecond = FRotator(0.0f, 90.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float LatestDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth = 10.0f;
	ARotatingMesh();
	virtual void Tick(float DeltaSeconds) override;
	virtual float ApplyDamage_Implementation(float InDamage) override;
	void SetLatestDamage(float InDamage);
};
