// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AmmoType.h"
#include "AmmoDataTable.generated.h"

/**
 * 
 */
UCLASS()
class GROUPUNREALPROJECT_API UAmmoDataTable : public UDataTable
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TArray<FAmmoType> ammoTypes;
};
