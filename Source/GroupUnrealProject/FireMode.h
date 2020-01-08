// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireMode.generated.h"


UENUM()
enum EFireMode
{
	semiAutomatic = 0,
	fullAuto,
	burstFire,
	singleAction //Launcher or sniper for example
};
