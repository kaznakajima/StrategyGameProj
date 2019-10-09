// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "CharacterInterface.h"
#include "BattleCharacterData.generated.h"

// 
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	// 所属チーム
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

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
		int Power;

	// 防御力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Defence;

	// 回避力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Avoid;
};

USTRUCT(BlueprintType)
struct FCharacterDataAssetRecord
{
	GENERATED_USTRUCT_BODY()
public:

	// 所属チーム
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

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
		int Power;

	// 防御力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Defence;

	// 回避力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Avoid;
};

// 戦闘用キャラクターのステータスデータ
UCLASS()
class STRATEGYPROJ_API UBattleCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	// データテーブル
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditData")
		UDataTable* DataTable;
#endif
	// テーブルをインポートする
	UFUNCTION(meta = (CallInEditor = "true"))
		void Import();

	// データリスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FCharacterDataAssetRecord> Data;
};
