// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

#include "GroupUnrealProjectCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AGroupUnrealProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	UPROPERTY()
	class AWeaponBase* CurrentWeapon = nullptr;
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	



public:
	AGroupUnrealProjectCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon Pickup Box")
		UBoxComponent* WeaponPickupBox = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsFiring = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FiringAxisValue;

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AGroupUnrealProjectProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UFUNCTION(BlueprintCallable)
		void OnFire();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void DropWeapon();
		void DropWeapon_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ChangeMagazine();
		void ChangeMagazine_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ChangeBullets();
		void ChangeBullets_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ChangeWeaponSkin();
		void ChangeWeaponSkin_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
		void ChangeFiremode();
		void ChangeFiremode_Implementation();


protected:


	
	void MoveForward(float Val);

	
	void MoveRight(float Val);

	
	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);


	

	
protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:
	
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	

};

