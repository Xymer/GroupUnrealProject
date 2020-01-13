
#pragma once

#include "CoreMinimal.h"
#include "MagazineBase.h"
#include "BulletBase.h"

#include "Ammo.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)

struct GROUPUNREALPROJECT_API FAmmo
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
        int CurrentAmmo;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
        TSubclassOf<UMagazineBase> magazine;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
        TSubclassOf<UBulletBase> bullets;
    
};
