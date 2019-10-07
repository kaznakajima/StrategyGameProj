// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterInterface.generated.h"

UINTERFACE()
class STRATEGYPROJ_API UCharacterInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// キャラクターの装備状態
UENUM(BlueprintType)
enum class EEquipmentState : uint8
{
	NONE = 0						UMETA(DisplayName = "None"),
	SWORD = 1					UMETA(DisplayName = "Sword"),
	DOUBLE_SWORD = 2		UMETA(DisplayName = "Double_Sword"),
	SHILD = 4						UMETA(DisplayName = "SHILD"),
	SWORD_SHILD = 8		UMETA(DisplayName = "Sword_Shild"),
	MAGICWAND = 16			UMETA(DisplayName = "MagicWand"),
	BOW = 32						UMETA(DisplayName = "BOW"),
};

// キャラクターステータス
USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_USTRUCT_BODY()

	// キャラクターの装備状態
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	EEquipmentState MyState;

	// キャラクター名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FText Name;

	// HP(体力)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int MaxHP;

	// SP(スキルポイント)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int MaxSP;

	// 攻撃力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int STR;

	// 防御力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int DEF;

	// 回避力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int AVO;
};

// キャラクターインターフェイス
class STRATEGYPROJ_API ICharacterInterface
{
	GENERATED_IINTERFACE_BODY()

public:

};
