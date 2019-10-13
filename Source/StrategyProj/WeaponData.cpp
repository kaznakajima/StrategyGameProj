// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponData.h"

// データをインポートする
void UWeaponData::Import()
{
#if WITH_EDITORONLY_DATA
	if (!DataTable ||
		!DataTable->GetRowStruct()->IsChildOf(FWeaponStatusData::StaticStruct()))
	{
		return;
	}

	// データをリセット
	Data.Empty();

	// データの行数を取得
	auto Names = DataTable->GetRowNames();

	// データの取得
	for (int i = 0; i < Names.Num(); i++)
	{
		// データの抽出
		auto record = DataTable->FindRow<FWeaponStatusData>(Names[i], FString());

		// 値の設定
		FWeaponDataAssetRecord asset;
		asset.HP = record->HP;
		asset.SP = record->SP;
		asset.STR = record->STR;
		asset.DEF = record->DEF;
		asset.AVO = record->AVO;

		Data.Add(asset);
	}

#endif
}
