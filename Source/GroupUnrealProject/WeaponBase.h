// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"


#include "FireMode.h"
#include "MagazineComponent.h"
#include "BulletComponent.h"
#include "HitScanComponent.h"
#include "ProjectileComponent.h"


#include "Templates\SubclassOf.h"
#include "Particles/ParticleSystemComponent.h"
#include "WeaponBase.generated.h"

UCLASS()

class GROUPUNREALPROJECT_API AWeaponBase : public AActor
{

	GENERATED_BODY()
private:
	
	int CurrentSelectedSkin = 0;
	
	FHitResult HitResult;
	bool bShootDelayDone;
	
	bool bReloadTimeDone;
public:

	float TempReloadTime;
	bool bHasFired = false;
	int CurrentBurst = 0;
	//EFireMode CurrentFireMode;
	class UHitScanComponent* HitScanComponent;
	class UProjectileComponent* ProjectileComponent;
	class UAudioComponent* AudioComponent;
	class UParticleSystemComponent* ParticleComponent;
	class UGameplayStatics* GameplayStaticComponent;
	class UBulletComponent* BulletComponent;
	class UMagazineComponent* MagazineComponent;

	/*Skeletal mesh need Muzzle bone*/
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (Tooltip = "Your skeletal mesh need a Muzzle bone to function (It's case sensetive)"))
		USkeletalMeshComponent* WeaponMesh ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		class UBoxComponent* TriggerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		TArray<UMaterialInterface*> Skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin")
		UMaterialInterface* CurrentSkin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<EFireMode> CurrentFireMode = EFireMode::SemiAutomatic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		FVector MuzzlePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		float GeneralDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		float ShootDelay = 0.05f;
		float TempShootDelay = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		int BurstFireCount = 3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Reloading")
		bool bIsReloading;

	
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void ShootWeapon(FVector CameraForwardVector, bool bIsFiring);

	UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly, Category = "Weapon Functions")
		void ReloadWeapon();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Weapon Functions")
		void SwitchMagazine();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Weapon Functions")
		void SwitchBullets();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Weapon Functions")
		void SwitchSkin();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Weapon Functions")
		void SwitchFireMode();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Ammo")
		void AddToAmmoReserve(int Amount);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Ammo")
		int DeductFromAmmoReserve(int Amount);

private:
		void StartLineTrace(FVector CameraForwardVector);
		void PlayShootSound();
		void SpawnParticles();
		void InitializeWeaponBase();
};
