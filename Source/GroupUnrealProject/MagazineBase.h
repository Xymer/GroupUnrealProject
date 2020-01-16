// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MagazineBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UMagazineBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		FName MagazineType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		 int MagazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		float ReloadSpeed;
};
