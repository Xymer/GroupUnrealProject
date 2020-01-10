// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "AmmoType.generated.h"
/**
 *
 */
USTRUCT(BlueprintType)
struct GROUPUNREALPROJECT_API FAmmoType
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoType")
			FName ammoType;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoType")
			float damage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoType")
			float projectileSpeed;
};
