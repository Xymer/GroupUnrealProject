// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileBase.h"
#include "ProjectileComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GROUPUNREALPROJECT_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		TSubclassOf<class AProjectileBase> WeaponProjectile;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Projectile Properties")
		FVector ProjectileStart;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Projectile Properties")
		FRotator ProjectileRotation;

	// Sets default values for this component's properties
	UProjectileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Projectile Function")
		void ProjectileFireWeapon();
	FActorSpawnParameters WeaponSpawnParameter;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
