// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Math/Vector.h"


#include "FireMode.h"
#include "MagazineBase.h"
#include "BulletBase.h"
#include "HitScanComponent.h"
#include "ProjectileComponent.h"

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
	EFireMode CurrentFireMode;
	FHitResult HitResult;
	bool bShootDelayDone;

public:

	bool bHasFired = false;
	int CurrentBurst = 0;
	class UHitScanComponent* HitScanComponent;
	class UProjectileComponent* ProjectileComponent;
	/*Skeletal mesh need Muzzle bone*/
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		class UBoxComponent* TriggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		TArray<UMaterialInterface*> Skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		UMaterialInterface* CurrentSkin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UMagazineBase>> AvailableMagazines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TArray <TSubclassOf<UBulletBase>> AvailableBullets;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
		UMagazineBase* CurrentMagazine;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
		UBulletBase* CurrentBullet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
		int CurrentMagazineAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<EFireMode> FireMode = EFireMode::SemiAutomatic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		FVector MuzzlePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		float ShootDelay = 0.05f;
		float TempShootDelay = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		int BurstFireCount = 3;
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void ShootWeapon(FVector CameraForwardVector, bool bIsFiring);

	UFUNCTION()
		void ReloadWeapon();

	UFUNCTION()
		void SwitchMagazine();

	UFUNCTION()
		void SwitchBullets();

	UFUNCTION()
		void SwitchSkin();
	UFUNCTION()
		void SwitchFireMode();

};
