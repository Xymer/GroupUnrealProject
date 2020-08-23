// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GroupUnrealProjectCharacter.h"
#include "GroupUnrealProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponBase.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AGroupUnrealProjectCharacter

AGroupUnrealProjectCharacter::AGroupUnrealProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	WeaponPickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Pickup Box"));
	WeaponPickupBox->InitBoxExtent(FVector(60.0f, 60.0f,60.0f));
	WeaponPickupBox->SetupAttachment(GetCapsuleComponent());
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void AGroupUnrealProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	WeaponPickupBox->OnComponentBeginOverlap.AddDynamic(this, &AGroupUnrealProjectCharacter::OnBeginOverlap);
	//Mesh1P->SetHiddenInGame(false, true);
}



#pragma region Input



void AGroupUnrealProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	// Bind fire event
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGroupUnrealProjectCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AGroupUnrealProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGroupUnrealProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGroupUnrealProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGroupUnrealProjectCharacter::LookUpAtRate);
}








void AGroupUnrealProjectCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->Tags.Contains("Weapon") && !CurrentWeapon)
		{
			PickupWeapon(OtherActor);
		}
	}
}

void AGroupUnrealProjectCharacter::PickupWeapon(AActor* OtherActor) {
	CurrentWeapon = Cast<AWeaponBase>(OtherActor);
	CurrentWeapon->WeaponMesh->SetSimulatePhysics(false);
	CurrentWeapon->WeaponMesh->SetCollisionProfileName("NoCollision");
	OtherActor->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
	OtherActor->SetActorTransform(Mesh1P->GetSocketTransform("GripPoint"));
	CurrentWeapon->SetOwner(this);
	CurrentWeapon->OnPickupWeapon();
}

void AGroupUnrealProjectCharacter::DropWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->DetachRootComponentFromParent(true);
		CurrentWeapon->WeaponMesh->SetSimulatePhysics(true);
		CurrentWeapon->WeaponMesh->SetCollisionProfileName("PhysicsActor");
		CurrentWeapon->OnDropWeapon();
		CurrentWeapon = nullptr;
	}
}

void AGroupUnrealProjectCharacter::ChangeMagazine()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SwitchMagazine();
	}
}

void AGroupUnrealProjectCharacter::ChangeBullets()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SwitchBullets();
	}
}

void AGroupUnrealProjectCharacter::ChangeWeaponSkin()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SwitchSkin();
	}
}

void AGroupUnrealProjectCharacter::ChangeFiremode()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SwitchFireMode();
	}
}

void AGroupUnrealProjectCharacter::ReloadCurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->ReloadWeapon();
	}
}

void AGroupUnrealProjectCharacter::ZoomIn()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->ZoomIn();
	}
}

void AGroupUnrealProjectCharacter::ZoomOut()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->ZoomOut();
	}
}

#pragma endregion


void AGroupUnrealProjectCharacter::OnFire()
{
	float Range = 1;
	if (CurrentWeapon)
	{
		if (CurrentWeapon->HitScanComponent)
		{
			Range = CurrentWeapon->HitScanComponent->HitScanRange;
		}
	}
	
	if (CurrentWeapon && FiringAxisValue > 0)
	{
		 CurrentWeapon->ShootWeapon(FirstPersonCameraComponent->GetForwardVector() * Range, bIsFiring);
	}
	if (CurrentWeapon && FiringAxisValue <= 0)
	{
		CurrentWeapon->bHasFired = false;
		CurrentWeapon->CurrentBurst = 0;
	}
}


void AGroupUnrealProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGroupUnrealProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGroupUnrealProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGroupUnrealProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


