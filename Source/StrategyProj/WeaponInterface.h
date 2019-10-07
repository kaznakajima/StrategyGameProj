// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

// íÌXe[^X
USTRUCT(BlueprintType)
struct FWeaponStatus
{
	GENERATED_USTRUCT_BODY()

	// HPâ³
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SPâ³
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

	// UÍâ³
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int STR;

	// häÍâ³
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int DEF;

	// ñðÍâ³
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int AVO;
};

class STRATEGYPROJ_API IWeaponInterface
{
	GENERATED_BODY()

public:
};
