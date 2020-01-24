// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingMesh.h"

ARotatingMesh::ARotatingMesh()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARotatingMesh::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float ARotatingMesh::ApplyDamage_Implementation(float InDamage)
{
	CurrentHealth -= InDamage;
	SetLatestDamage(InDamage);
	if (CurrentHealth <= 0.0f)
	{
		Destroy();
	}
	return CurrentHealth;
}

void ARotatingMesh::SetLatestDamage(float InDamage)
{
	LatestDamage = InDamage;
}


