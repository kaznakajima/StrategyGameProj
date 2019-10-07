// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	// HP(体力)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SP(スキルポイント)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

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

USTRUCT(BlueprintType)
struct FWeaponStatusData
{
	GENERATED_USTRUCT_BODY()

public:

	// HP(体力)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SP(スキルポイント)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

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

UCLASS()
class STRATEGYPROJ_API UWeaponData : public UDataAsset
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
		TArray<FWeaponStatusData> Data;
};
