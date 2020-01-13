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
	if ( AvailableMagazines.Num() <= TotalMags)
	{
	CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[1]);
	}
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::ShootWeapon()
{
}

void AWeaponBase::ReloadWeapon()
{
}

