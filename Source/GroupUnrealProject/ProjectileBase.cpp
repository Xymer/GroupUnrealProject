// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "DamagableInterface.h"

#include "TimerManager.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets up collision Sphere
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(ProjectileSize);
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	//sets up the projectile trail(particle system)
	ProjectileParticleTrail = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("Weapon Particle System"));
	ProjectileParticleTrail->SetupAttachment(CollisionComponent);

	//sets default for movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	//The projectile movement values being overridden with the bases values
	
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->ProjectileGravityScale = ProjectileWeight;
	ProjectileMovement->Bounciness = ProjectileBounch;
	ProjectileMovement->Friction = ProjectileFriction;;

	if (ProjectileBounch <= 0)
	{
		ProjectileMovement->bShouldBounce = false;
	}

	//starts action when the life ends
	if (ActionThatHappensOnImpact)
	{
		GetWorldTimerManager().SetTimer(ProjectileTimer, this, &AProjectileBase::ActionAfterFuseTime, 2.0f, true, FuseTime);
	}
	else
		nullptr;


}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp)
	{
		if (Cast<IDamagableInterface>(OtherActor))
		{
			IDamagableInterface* tempActor = Cast<IDamagableInterface>(OtherActor);
			tempActor->ApplyDamage_Implementation(ProjectileDamage);
			ActionAfterFuseTime();
			Destroy();
		}

				//Action that starts on impact(if selected)
		if (bCauseActionOnImpact == true)
		{
			ActionAfterFuseTime();
		}

		//destroys projectile on impact(if selected)
		if (bDestroyOnImpact == true)
		{
			Destroy();
		}

	}
}

void AProjectileBase::ActionAfterFuseTime()
{

	if (ActionThatHappensOnImpact)
	{

		FActorSpawnParameters ActionSpawnParameters;
		ActionSpawnParameters.Owner = this;
		FVector spawnLocation = this->RootComponent->GetComponentLocation();
		FRotator ProjectileRotation = this->RootComponent->GetComponentRotation();

		UWorld* world = GetWorld();
		if (world)
		{
			world->SpawnActor<AProjectileImpactAction>(ActionThatHappensOnImpact, spawnLocation, ProjectileRotation, ActionSpawnParameters);
		}


	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Action Selected"));

	}

	GetWorldTimerManager().ClearTimer(ProjectileTimer);
	Destroy();
}

void AProjectileBase::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;

}

