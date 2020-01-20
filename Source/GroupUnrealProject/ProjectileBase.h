// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine.h>
#include "ProjectileBase.generated.h"

UCLASS()
class GROUPUNREALPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile Settings")
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile Settings")
		UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		float ProjectileSpeed;			//Base Speed of the projectile

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		float ProjectileWeight;			//Base Weight of the projectile(How heavy is the down force gonna be)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		float ProjectileBounch;			//How Bounch-y is the projectile going to be, Overwatch´s Junkrats Primary fire compared to Team Fortress 2´s Demomans Primary weapon fire

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		float ProjectileFriction;		//How much will the projectile be able to roll on the floor(Demomans Stock Grenade launcher projectiles as a reference)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		float FuseTime;					//Projectile Timer, Time it takes for it to activate its second action(if it has any or wont activate up instantly)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		int ProjectileDamage;			//The base direct hit damage

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		bool bActionOnImpact;			//Does the projectile spawn a different actor on impact(example: Spawning Explosion actor to simulate a explosive

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		bool bDestroyOnImpact;			//Does the projectile Activate on Impact or does it need another condition to activate

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

};
