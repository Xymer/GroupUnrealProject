// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/BoxComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/Engine.h>

// Sets default values
AWeaponBase::AWeaponBase()
{
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeleton"));
	WeaponMesh->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(25.0f, 25.0f, 25.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	
}



// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	if (!this->ActorHasTag("Weapon"))
	{
		this->Tags.Add("Weapon");
	}
	Super::BeginPlay();
	if (WeaponMesh != nullptr)
	{
		MuzzlePoint = WeaponMesh->GetSocketLocation("Muzzle");
	}

	CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
	CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
	CurrentUsedMagazine = CurrentMagazine->magazineSize;

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TestTimer -= DeltaTime;
	

}

void AWeaponBase::ShootWeapon()
{
}

void AWeaponBase::ReloadWeapon()
{
}


void AWeaponBase::SwitchMagazine()
{
	SelectedMagazine++;
	if (SelectedMagazine > AvailableMagazines.Num())
	{
		SelectedMagazine = 0;
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		CurrentUsedMagazine = CurrentMagazine->magazineSize;
	}

	else if (SelectedMagazine < AvailableMagazines.Num())
	{
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		CurrentUsedMagazine = CurrentMagazine->magazineSize;
	}
}

void AWeaponBase::SwitchBullets()
{
	SelectedBullets++;
	if (SelectedBullets > AvailableBullets.Num() - 1)
	{
		SelectedBullets = 0;
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
	}

	else if (SelectedBullets < AvailableBullets.Num() - 1)
	{	
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
	}
}

void AWeaponBase::SwitchSkin()
{
	if (CurrentSelectedSkin < Skin.Num() - 1)
	{
		CurrentSelectedSkin++;
		CurrentSkin = Skin[CurrentSelectedSkin];
		WeaponMesh->SetMaterial(0, CurrentSkin);
	}
	else if(CurrentSelectedSkin > Skin.Num() - 1)
	{
		CurrentSelectedSkin = 0;
		CurrentSkin = Skin[CurrentSelectedSkin];
		WeaponMesh->SetMaterial(0, CurrentSkin);
	}
}



