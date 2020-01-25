// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileImpactAction.generated.h"

UCLASS()
class GROUPUNREALPROJECT_API AProjectileImpactAction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileImpactAction();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Action Properties")
		class USphereComponent* ActionRadiusCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Properties")
		float ExplsionsRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Properties")
		float ExplosionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Properties")
		UParticleSystem* ActionParticleEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Properties")
		float ParticleSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Properties")
		float DebugTime = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnExplosionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
