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
	InitializeWeaponBase();
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
	if (bIsReloading)
	{	
		TempReloadTime -= DeltaTime;
		if (TempReloadTime <= 0)
		{
			CurrentMagazineAmmoCount = DeductFromAmmoReserve(CurrentMagazine->MagazineSize);
			bIsReloading = false;
		}
	}
}

void AWeaponBase::ShootWeapon(FVector CameraForwardVector, bool bIsFiring)
{
	if (HitScanComponent && CurrentMagazineAmmoCount > 0 && !bIsReloading)
	{
		if (CurrentFireMode == SemiAutomatic && bIsFiring && !bHasFired)
		{
			StartLineTrace(CameraForwardVector);
		
			bHasFired = true;
		}

		if (CurrentFireMode == BurstFire && !bHasFired)
		{			
			if (CurrentBurst < BurstFireCount && CurrentMagazineAmmoCount > 0)
			{
				StartLineTrace(CameraForwardVector);
				
				CurrentBurst++;
			}
			else if (CurrentBurst > BurstFireCount || CurrentMagazineAmmoCount == 0)
			{
				bHasFired = true;
			}
		}
		if (CurrentFireMode == FullAuto  && bShootDelayDone)
		{
			StartLineTrace(CameraForwardVector);
		}
		
	}	
	if (ProjectileComponent)
	{
		
	}
	if (CurrentMagazineAmmoCount <= 0 && !bIsReloading)
	{
		ReloadWeapon();
	}
}

void AWeaponBase::ReloadWeapon()
{
	
	if ( AmmoReserve != 0 && CurrentMagazineAmmoCount != CurrentMagazine->MagazineSize)
	{
	bIsReloading = true;
	TempReloadTime = CurrentMagazine->ReloadSpeed;
	}
}


void AWeaponBase::SwitchMagazine()
{
	SelectedMagazine++;
	if (SelectedMagazine > AvailableMagazines.Num())
	{
		SelectedMagazine = 0;
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		ReloadWeapon();
	}

	else if (SelectedMagazine < AvailableMagazines.Num())
	{
		CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
		ReloadWeapon();
	}
	
}

void AWeaponBase::SwitchBullets()
{
	SelectedBullets++;
	if (SelectedBullets > AvailableBullets.Num() - 1)
	{
		SelectedBullets = 0;
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
		ReloadWeapon();
	}

	else if (SelectedBullets < AvailableBullets.Num() - 1)
	{
		CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
		ReloadWeapon();
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

void AWeaponBase::AddToAmmoReserve(int Amount)
{
	AmmoReserve += Amount;
	if (AmmoReserve >= MaxAmmoReserve)
	{
		AmmoReserve = MaxAmmoReserve;
	}
}

int AWeaponBase::DeductFromAmmoReserve(int Amount)
{
	int TempAmmoReserve;
	if (CurrentMagazineAmmoCount + AmmoReserve < Amount)
	{	
			TempAmmoReserve = AmmoReserve;
			AmmoReserve = 0;
			return TempAmmoReserve + CurrentMagazineAmmoCount;	
	}
	else
	{
	AmmoReserve -= (Amount - CurrentMagazineAmmoCount);
	return Amount;
	}
}

void AWeaponBase::StartLineTrace(FVector CameraForwardVector)
{
	HitResult = HitScanComponent->LineTrace(WeaponMesh->GetSocketLocation("Muzzle"), CameraForwardVector);
	PlayShootSound();
	SpawnParticles();
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.Actor->GetName());
		if (Cast<IDamagableInterface>(HitResult.GetActor()))
		{
		Cast<IDamagableInterface>(HitResult.GetActor())->Execute_ApplyDamage(HitResult.GetActor(),CurrentBullet->BulletDamage);
		}
	}
	CurrentMagazineAmmoCount--;
}

void AWeaponBase::PlayShootSound()
{
	if (AudioComponent)
	{
	AudioComponent->Play();
	}
}

void AWeaponBase::SpawnParticles()
{
	if (ParticleComponent)
	{
		ParticleComponent->SetActive(true,true);
	}
}

void AWeaponBase::InitializeWeaponBase()
{
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
	if (!AudioComponent)
	{
		if (this->FindComponentByClass<UAudioComponent>())
		{
			AudioComponent = this->FindComponentByClass<UAudioComponent>();
		}
	}

	if (!ParticleComponent)
	{
		if (this->FindComponentByClass<UParticleSystemComponent>())
		{
			ParticleComponent = this->FindComponentByClass<UParticleSystemComponent>();
			ParticleComponent->SetWorldLocation(WeaponMesh->GetSocketLocation("Muzzle"));
		}
	}

	if (Skin.Num() != 0)
	{
		CurrentSkin = Skin[0];
	}
	// Need to change when bullets and magazine are components
	CurrentMagazine = NewObject<UMagazineBase>(GetTransientPackage(), *AvailableMagazines[SelectedMagazine]);
	CurrentBullet = NewObject<UBulletBase>(GetTransientPackage(), *AvailableBullets[SelectedBullets]);
	CurrentMagazineAmmoCount = CurrentMagazine->MagazineSize;
	CurrentFireMode = SemiAutomatic;
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetCollisionProfileName("PhysicsActor");
}





