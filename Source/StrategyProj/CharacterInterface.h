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
enum class ECharacterTeam : uint8
{
	Team1		UMETA(DisplayName = "PlayerTeam"),
	Team2		UMETA(DisplayName = "EnemyTeam")
};

// キャラクターの装備状態
UENUM(BlueprintType)
enum class EEquipmentState : uint8
{
	NONE = 0						UMETA(DisplayName = "NONE"),
	SWORD = 1					UMETA(DisplayName = "SWORD"),
	DOUBLE_SWORD = 2		UMETA(DisplayName = "DOUBLE_SWORD"),
	SHILD = 4						UMETA(DisplayName = "SHILD"),
	SWORD_SHILD = 8		UMETA(DisplayName = "SWORD_SHILD"),
	MAGICWAND = 16			UMETA(DisplayName = "MAGICWAND"),
	BOW = 32						UMETA(DisplayName = "BOW"),
};

// 戦闘時のアクション
UENUM(BlueprintType)
enum class EBattleState : uint8
{
	ATTACK			UMETA(DisplayName = "ATTACK"),
	GARD			UMETA(DisplayNama = "GARD"),
	AVOID			UMETA(DisplayName = "AVOID"),
	SKILL			UMETA(DisplayName = "SKILL"),
};

// キャラクターステータス
USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_USTRUCT_BODY()

	// 所属チーム
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

	// キャラクターの装備状態
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EEquipmentState MyState;

	// キャラクターの装備状態
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EBattleState BattleState;

	// キャラクター名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FText Name;

	// HP(体力)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float MaxHP;

	// SP(スキルポイント)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float MaxSP;

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
