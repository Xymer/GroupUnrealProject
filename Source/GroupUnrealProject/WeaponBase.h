// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireMode.h"
#include "Math/Vector.h"
#include "MagazineBase.h"
#include "BulletBase.h"
#include "Templates\SubclassOf.h"
#include "WeaponBase.generated.h"


UCLASS()

class GROUPUNREALPROJECT_API AWeaponBase : public AActor
{

	GENERATED_BODY()
private:
	int SelectedBullets = 0;
	int SelectedMagazine = 0;
	int CurrentSelectedSkin = 0;
	float TestTimer = 5;

public:

	/*Skeletal mesh need Muzzle bone*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		TArray<UMaterialInterface*> Skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		UMaterialInterface* CurrentSkin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UMagazineBase>> AvailableMagazines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UBulletBase>> AvailableBullets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		UMagazineBase* CurrentMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		UBulletBase* CurrentBullet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
		int CurrentUsedMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<EFireMode> FireMode = EFireMode::semiAutomatic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		FVector MuzzlePoint;
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ShootWeapon();
		void ShootWeapon_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ReloadWeapon();
		void ReloadWeapon_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void SwitchMagazine();
		void SwitchMagazine_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void SwitchBullets();
		void SwitchBullets_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void SwitchSkin();
		void SwitchSkin_Implementation();
};
