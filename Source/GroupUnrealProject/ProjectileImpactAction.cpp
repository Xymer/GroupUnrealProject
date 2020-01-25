// Fill out your copyright notice in the Description page of Project Settings.



#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "DamagableInterface.h"
#include "DrawDebugHelpers.h"
#include "ProjectileImpactAction.h"

// Sets default values
AProjectileImpactAction::AProjectileImpactAction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionRadiusCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ActionRadiusCollider->InitSphereRadius(ExplsionsRadius);
	ActionRadiusCollider->SetupAttachment(RootComponent);
	ActionRadiusCollider->SetCollisionProfileName(TEXT("Trigger"));
	ActionRadiusCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectileImpactAction::OnExplosionOverlap);
}


// Called when the game starts or when spawned
void AProjectileImpactAction::BeginPlay()
{
	Super::BeginPlay();
	ActionRadiusCollider->SetSphereRadius(ExplsionsRadius);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActionParticleEffect, GetActorLocation());
}

// Called every frame
void AProjectileImpactAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileImpactAction::OnExplosionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp)
	{
		if (Cast<IDamagableInterface>(OtherActor))
		{
			IDamagableInterface* tempActor = Cast<IDamagableInterface>(OtherActor);
			tempActor->ApplyDamage_Implementation(ExplosionDamage);
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "pew");
			DrawDebugSphere(GetWorld(), this->GetOwner()->GetActorLocation(), ExplsionsRadius,12, FColor::Red, false, DebugTime);
			Destroy();
		}

	}
	
}

