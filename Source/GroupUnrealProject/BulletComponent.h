// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletBase.h"
#include "BulletComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPUNREALPROJECT_API UBulletComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	int SelectedBullets = 0;
	// Sets default values for this component's properties
	UBulletComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
		TArray <TSubclassOf<UBulletBase>> AvailableBullets;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
		UBulletBase* CurrentBullet;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitializeBullet();
	void SwitchBullet();
		
};
