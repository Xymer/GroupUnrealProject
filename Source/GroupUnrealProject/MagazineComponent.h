// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagazineBase.h"
#include "MagazineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPUNREALPROJECT_API UMagazineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	int SelectedMagazine = 0;
	
	UMagazineComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
		TArray <TSubclassOf<UMagazineBase>> AvailableMagazines;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magazine")
		UMagazineBase* CurrentMagazine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
		int CurrentMagazineAmmoCount;
	// Make an Array
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		int AmmoReserve = 120;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		int MaxAmmoReserve = 360;
	//****
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitalizeMagazine();
	void DeductFromCurrentMagazineCount();
	int DeductFromAmmoReserve(int Amount);
	void AddToAmmoReserve(int Amount);
	void ReloadMagazine();
	void SwitchMagazine();
	
		
};
