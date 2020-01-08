// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/Engine.h>

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	if (weaponMesh != nullptr)
	{

	muzzlePoint = weaponMesh->GetSocketLocation("Muzzle");
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, muzzlePoint.ToString());
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

