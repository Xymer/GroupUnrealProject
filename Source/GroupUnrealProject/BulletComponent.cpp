// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletComponent.h"
#include "WeaponBase.h"
// Sets default values for this component's properties
UBulletComponent::UBulletComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBulletComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBulletComponent::InitializeBullet()
{
	CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
}

void UBulletComponent::SwitchBullet()
{
	SelectedBullets++;
	if (SelectedBullets > AvailableBullets.Num() - 1)
	{
		SelectedBullets = 0;
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
		Cast<AWeaponBase>(GetOwner())->ReloadWeapon();
	}

	else if (SelectedBullets < AvailableBullets.Num() - 1)
	{
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
		Cast<AWeaponBase>(GetOwner())->ReloadWeapon();
	}

}

