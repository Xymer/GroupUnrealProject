// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/BoxComponent.h"
#include "DamagableInterface.h"
#include "GroupUnrealProjectCharacter.h"
#include "Camera/CameraComponent.h"
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
			if (MagazineComponent)
			{
				MagazineComponent->CurrentMagazineAmmoCount = DeductFromAmmoReserve(MagazineComponent->CurrentMagazine->MagazineSize);
			}
			bIsReloading = false;
		}
	}
}

void AWeaponBase::ShootWeapon(FVector CameraForwardVector, bool bIsFiring)
{
	if (HitScanComponent && MagazineComponent && MagazineComponent->CurrentMagazineAmmoCount > 0 && !bIsReloading)
	{
		if (CurrentFireMode == SemiAutomatic && bIsFiring && !bHasFired)
		{
			StartLineTrace(CameraForwardVector);

			bHasFired = true;
		}

		if (CurrentFireMode == BurstFire && !bHasFired)
		{
			if (CurrentBurst < BurstFireCount && MagazineComponent->CurrentMagazineAmmoCount > 0)
			{
				StartLineTrace(CameraForwardVector);

				CurrentBurst++;
			}
			else if (CurrentBurst > BurstFireCount || MagazineComponent->CurrentMagazineAmmoCount == 0)
			{
				bHasFired = true;
			}
		}
		if (CurrentFireMode == FullAuto && bShootDelayDone)
		{
			StartLineTrace(CameraForwardVector);
		}

	}
	if (ProjectileComponent)
	{

	}
	if (MagazineComponent && MagazineComponent->CurrentMagazineAmmoCount <= 0 && !bIsReloading)
	{
		ReloadWeapon();
	}
}

void AWeaponBase::ReloadWeapon()
{

	if (MagazineComponent)
	{
		MagazineComponent->ReloadMagazine();
	}
}


void AWeaponBase::SwitchMagazine()
{
	MagazineComponent->SwitchMagazine();
}

void AWeaponBase::SwitchBullets()
{
	if (BulletComponent)
	{
		BulletComponent->SwitchBullet();
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
	if (MagazineComponent)
	{
		MagazineComponent->AddToAmmoReserve(Amount);
	}
}

int AWeaponBase::DeductFromAmmoReserve(int Amount)
{
	if (MagazineComponent)
	{
		return MagazineComponent->DeductFromAmmoReserve(Amount);
	}
	else
	{
		return DefaultMagSize;
	}
}

void AWeaponBase::ZoomIn()
{
	if (ZoomComponent)
	{
		ZoomComponent->ZoomIn();
	}
}

void AWeaponBase::ZoomOut()
{
	if (ZoomComponent)
	{
		ZoomComponent->ZoomOut();
	}
}

void AWeaponBase::OnPickupWeapon()
{
	if (RecoilComponent)
	{
		if (Cast<AGroupUnrealProjectCharacter>(this->GetOwner())->Controller->CastToPlayerController())
		{
			RecoilComponent->Controller = Cast<AGroupUnrealProjectCharacter>(this->GetOwner())->Controller->CastToPlayerController();
		}
	}


	if (ZoomComponent)
	{
		ZoomComponent->CameraComponent = Cast<AGroupUnrealProjectCharacter>(this->GetOwner())->FirstPersonCameraComponent;
		ZoomComponent->DefaultZoomValue = ZoomComponent->CameraComponent->FieldOfView;
	}

}

void AWeaponBase::OnDropWeapon()
{

	if (ZoomComponent)
	{
		ZoomComponent->ZoomOutOnDropWeapon();
	}

	if (Controller)
	{
		Controller = nullptr;
	}
	this->SetOwner(nullptr);
}

void AWeaponBase::StartLineTrace(FVector CameraForwardVector)
{
	HitResult = HitScanComponent->LineTrace(WeaponMesh->GetSocketLocation("Muzzle"), CameraForwardVector);
	PlayShootSound();
	SpawnParticles();
	if (RecoilComponent)
	{
		RecoilComponent->AddRecoil();
	}
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.Actor->GetName());
		if (Cast<IDamagableInterface>(HitResult.GetActor()))
		{
			if (BulletComponent)
			{
				Cast<IDamagableInterface>(HitResult.GetActor())->Execute_ApplyDamage(HitResult.GetActor(), BulletComponent->CurrentBullet->BulletDamage);
			}
			else
			{
				Cast<IDamagableInterface>(HitResult.GetActor())->Execute_ApplyDamage(HitResult.GetActor(), DefaultDamage);
			}
		}
	}
	if (MagazineComponent)
	{
		MagazineComponent->DeductFromCurrentMagazineCount();
	}
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
		ParticleComponent->SetActive(true, true);
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
	if (!MagazineComponent)
	{
		if (this->FindComponentByClass<UMagazineComponent>())
		{
			MagazineComponent = this->FindComponentByClass<UMagazineComponent>();
			MagazineComponent->InitalizeMagazine();
		}
	}
	if (!BulletComponent)
	{
		if (this->FindComponentByClass<UBulletComponent>())
		{
			BulletComponent = this->FindComponentByClass<UBulletComponent>();
			BulletComponent->InitializeBullet();
		}
	}
	if (!ZoomComponent)
	{
		if (this->FindComponentByClass<UZoomComponent>())
		{
			ZoomComponent = this->FindComponentByClass<UZoomComponent>();
		}
	}
	if (!RecoilComponent)
	{
		if (this->FindComponentByClass<URecoilComponent>())
		{
			RecoilComponent = this->FindComponentByClass<URecoilComponent>();
		}
	}
	CurrentFireMode = SemiAutomatic;
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetCollisionProfileName("PhysicsActor");
}





