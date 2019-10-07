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

// 武器のステータス
USTRUCT(BlueprintType)
struct FWeaponStatus
{
	GENERATED_USTRUCT_BODY()

	// HP補正
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SP補正
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

	// 攻撃力補正
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int STR;

	// 防御力補正
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int DEF;

	// 回避力補正
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int AVO;
};

class STRATEGYPROJ_API IWeaponInterface
{
	GENERATED_BODY()

public:
};
