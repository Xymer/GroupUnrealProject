// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/Engine.h>

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeleton"));

}



// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponMesh != nullptr)
	{
		MuzzlePoint = WeaponMesh->GetSocketLocation("Muzzle");
	}

	//TODO: Make a function with a message and input to this
	if (EquippedMagazine > AvailableMagazines.Num())
	{
		EquippedMagazine = 0;
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[EquippedMagazine]);
		CurrentUsedMagazine = CurrentMagazine->magazineSize;
	}
	else if (EquippedMagazine == AvailableMagazines.Num())
	{
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[EquippedMagazine]);
		CurrentUsedMagazine = CurrentMagazine->magazineSize;
	}
	else if (EquippedMagazine < AvailableMagazines.Num())
	{
		EquippedMagazine++;
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[EquippedMagazine]);
		CurrentUsedMagazine = CurrentMagazine->magazineSize;
	}
	//TODO: Make a function with a message and input to this
	if (EquippedBullets > AvailableBullets.Num())
	{
		EquippedBullets = 0;
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[EquippedBullets]);
	}
	else if (EquippedBullets == AvailableBullets.Num())
	{
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[EquippedBullets]);
	}
	else if(EquippedBullets < AvailableBullets.Num())
	{
		EquippedBullets++;
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[EquippedBullets]);
	}

	
	
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TestTimer -= DeltaTime;
	//TODO: Add function to be able to switch skin inside game
	if (TestTimer <= 0)
	{
		if (CurrentSelectedSkin < Skin.Num()-1)
		{
			CurrentSelectedSkin++;
			CurrentSkin = Skin[CurrentSelectedSkin];
			WeaponMesh->SetMaterial(0, CurrentSkin);
		}
		else
		{
			CurrentSelectedSkin = 0;
			CurrentSkin = Skin[CurrentSelectedSkin];
			WeaponMesh->SetMaterial(0, CurrentSkin);
		}

		TestTimer = 5.0f;
	}
}

void AWeaponBase::ShootWeapon()
{
}

void AWeaponBase::ReloadWeapon()
{
}

