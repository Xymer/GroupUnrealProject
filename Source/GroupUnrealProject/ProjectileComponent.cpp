// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileComponent.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	ProjectileFireWeapon();

}


void UProjectileComponent::ProjectileFireWeapon() {
	AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(WeaponProjectile, ProjectileStart, ProjectileRotation, WeaponSpawnParameter);

	if (Projectile)
	{
		FVector const LaunchDirection = ProjectileRotation.Vector();
		Projectile->FireInDirection(LaunchDirection);
	}
}

// Called every frame
void UProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

