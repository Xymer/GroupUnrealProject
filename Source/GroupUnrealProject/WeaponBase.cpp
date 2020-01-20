// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/BoxComponent.h"
#include "DamagableInterface.h"
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
	Super::BeginPlay();

	
	if (!this->ActorHasTag("Weapon"))
	{
		this->Tags.Add("Weapon");
	}
	if (!HitScanComponent)
	{
		if (this->FindComponentByClass<UHitScanComponent>())
		{
			HitScanComponent = this->FindComponentByClass<UHitScanComponent>();
		}
		
	}
	if (!ProjectileComponent)
	{
		if (this->FindComponentByClass<UProjectileComponent>())
		{
		ProjectileComponent = this->FindComponentByClass<UProjectileComponent>();
		}
	}

	if (Skin.Num() != 0)
	{
		CurrentSkin = Skin[0];
	}
	CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
	CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
	CurrentMagazineAmmoCount = CurrentMagazine->MagazineSize;
	CurrentFireMode = SemiAutomatic;
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetCollisionProfileName("PhysicsActor");
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TempShootDelay -= DeltaTime;
	if (TempShootDelay <= 0)
	{
		bShootDelayDone = true;
		TempShootDelay = ShootDelay;
	}
	else if (TempShootDelay > 0)
	{
		bShootDelayDone = false;
	}
	

	
}

void AWeaponBase::ShootWeapon(FVector CameraForwardVector, bool bIsFiring)
{
	//TODO: Rewrite HitResult to function
	if (HitScanComponent)
	{
		if (CurrentFireMode == SemiAutomatic && bIsFiring && !bHasFired)
		{
			HitResult = HitScanComponent->LineTrace(WeaponMesh->GetSocketLocation("Muzzle"), CameraForwardVector);
			if (HitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.Actor->GetName());
			}
			bHasFired = true;
		}

		if (CurrentFireMode == BurstFire && !bHasFired)
		{			
			if (CurrentBurst < BurstFireCount)
			{
				HitResult = HitScanComponent->LineTrace(WeaponMesh->GetSocketLocation("Muzzle"), CameraForwardVector);
				if (HitResult.GetActor())
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.Actor->GetName());
				}
				CurrentBurst++;
			}
			else if (CurrentBurst > BurstFireCount)
			{
				bHasFired = true;
			}
		}
		if (CurrentFireMode == FullAuto  && bShootDelayDone)
		{
			HitResult = HitScanComponent->LineTrace(WeaponMesh->GetSocketLocation("Muzzle"), CameraForwardVector);
			if (HitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.Actor->GetName());
			}
		}
	}
	else
	{

	}

	if (ProjectileComponent)
	{
		
	}


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
		CurrentMagazineAmmoCount = CurrentMagazine->MagazineSize;
	}

	else if (SelectedMagazine < AvailableMagazines.Num())
	{
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		CurrentMagazineAmmoCount = CurrentMagazine->MagazineSize;
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
	CurrentSelectedSkin++;
	if (CurrentSelectedSkin <= Skin.Num() - 1)
	{
		CurrentSkin = Skin[CurrentSelectedSkin];
		WeaponMesh->SetMaterial(0, CurrentSkin);
	}
	else if (CurrentSelectedSkin > Skin.Num() - 1)
	{
		CurrentSelectedSkin = 0;
		CurrentSkin = Skin[CurrentSelectedSkin];
		WeaponMesh->SetMaterial(0, CurrentSkin);
	}
}

void AWeaponBase::SwitchFireMode()
{
	switch (CurrentFireMode)
	{
		case SemiAutomatic:
			CurrentFireMode = BurstFire;
			break;
		case BurstFire:
			CurrentFireMode = FullAuto;
			break;
		case FullAuto:
			CurrentFireMode = SemiAutomatic;
			break;
	}
}





