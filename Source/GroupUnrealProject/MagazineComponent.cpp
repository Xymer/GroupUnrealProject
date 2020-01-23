// Fill out your copyright notice in the Description page of Project Settings.


#include "MagazineComponent.h"
#include "WeaponBase.h"

// Sets default values for this component's properties
UMagazineComponent::UMagazineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMagazineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMagazineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMagazineComponent::InitalizeMagazine()
{
	CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
	CurrentMagazineAmmoCount = CurrentMagazine->MagazineSize;
}

void UMagazineComponent::DeductFromCurrentMagazineCount()
{
	CurrentMagazineAmmoCount--;
}

int UMagazineComponent::DeductFromAmmoReserve(int Amount)
{
	int TempAmmoReserve;
	if (CurrentMagazineAmmoCount + CurrentAmmoReserve[SelectedAmmoReserve] < Amount)
	{
		TempAmmoReserve = CurrentAmmoReserve[SelectedAmmoReserve];
		CurrentAmmoReserve[SelectedAmmoReserve] = 0;
		return TempAmmoReserve + CurrentMagazineAmmoCount;
	}
	else
	{
		CurrentAmmoReserve[SelectedAmmoReserve] -= (Amount - CurrentMagazineAmmoCount);
		return Amount;
	}
}

void UMagazineComponent::AddToAmmoReserve(int Amount)
{
	CurrentAmmoReserve[SelectedAmmoReserve] += Amount;
	if (CurrentAmmoReserve[SelectedAmmoReserve] >= MaxAmmoReserve[SelectedAmmoReserve])
	{
		CurrentAmmoReserve[SelectedAmmoReserve] = MaxAmmoReserve[SelectedAmmoReserve];
	}
}

void UMagazineComponent::ReloadMagazine()
{
	if (CurrentAmmoReserve[SelectedAmmoReserve] != 0 && !Cast<AWeaponBase>(GetOwner())->bIsReloading)
	{
		Cast<AWeaponBase>(GetOwner())->bIsReloading = true;
		Cast<AWeaponBase>(GetOwner())->TempReloadTime = CurrentMagazine->ReloadSpeed;
	}
}

void UMagazineComponent::SwitchMagazine()
{
	SelectedMagazine++;
	if (SelectedMagazine > AvailableMagazines.Num())
	{
		SelectedMagazine = 0;
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		Cast<AWeaponBase>(GetOwner())->ReloadWeapon();
	}

	else if (SelectedMagazine < AvailableMagazines.Num())
	{
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		Cast<AWeaponBase>(GetOwner())->ReloadWeapon();
	}

}

