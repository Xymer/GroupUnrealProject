// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Magazine.generated.h"

USTRUCT(BlueprintType)
struct FMagazine
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		int magazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		float reloadTime;
};
