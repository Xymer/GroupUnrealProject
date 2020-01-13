// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireMode.h"
#include "Math/Vector.h"
#include "MagazineBase.h"
#include "Ammo.h"
#include "Templates\SubclassOf.h"
#include "UObject\SoftObjectPtr.h"
#include "UObject/ObjectMacros.h"
#include "WeaponBase.generated.h"


UCLASS()

class GROUPUNREALPROJECT_API AWeaponBase : public AActor
{
	
	GENERATED_BODY()
private:	
	int TotalMags = 2;

public:
	
	/*Skeletal mesh need Muzzle bone*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UMagazineBase>> AvailableMagazines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UBulletBase>> AvailableBullets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray<FAmmo> Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<EFireMode> FireMode = EFireMode::semiAutomatic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		FVector MuzzlePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		UMagazineBase* CurrentMagazine;
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ShootWeapon();
	virtual void ReloadWeapon();
};
