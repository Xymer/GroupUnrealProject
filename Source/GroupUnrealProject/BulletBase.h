// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BulletBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class  UBulletBase : public UObject
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
		FName AmmoName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
		float BulletDamage;
};
