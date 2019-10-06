// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleCharacterData.h"

// データをインポートする
void UBattleCharacterData::Import()
{
#if WITH_EDITORONLY_DATA
	if (!DataTable ||
		!DataTable->GetRowStruct()->IsChildOf(FMyData::StaticStruct()))
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
		auto record = DataTable->FindRow<FMyData>(Names[i], FString());

		// 値の設定
		FCharacterDataAssetRecord asset;
		asset.MyState = record->MyState;
		asset.Name = FText::FromName(Names[i]);
		asset.MaxHP = record->MaxHP;
		asset.MaxSP = record->MaxSP;
		asset.Power = record->Power;
		asset.Defence = record->Defence;
		asset.Avoid = record->Avoid;

		Data.Add(asset);
	}

#endif
}
