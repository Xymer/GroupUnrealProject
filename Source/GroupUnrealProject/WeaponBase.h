// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireMode.h"
#include "Math/Vector.h"

#include "WeaponBase.generated.h"


UCLASS()

class GROUPUNREALPROJECT_API AWeaponBase : public AActor
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		float damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		int magazineSize = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		TEnumAsByte<EFireMode> fireMode = EFireMode::semiAutomatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		FVector muzzlePoint;



	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ShootWeapon();
	virtual void ReloadWeapon();
};
