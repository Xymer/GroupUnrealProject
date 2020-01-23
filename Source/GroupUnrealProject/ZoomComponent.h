// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "ZoomComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUPUNREALPROJECT_API UZoomComponent : public UActorComponent
{
	GENERATED_BODY()
		

public:	
	// Sets default values for this component's properties

	float DefaultZoomValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
		float ZoomValue = 30.0f;
	class UCameraComponent* CameraComponent;
	bool bTickEnabled = false;
	UZoomComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ZoomIn();
	void ZoomOut();
	void ZoomOutOnDropWeapon();
		

};
