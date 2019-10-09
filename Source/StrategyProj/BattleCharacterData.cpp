// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleCharacterData.h"

// �f�[�^���C���|�[�g����
void UBattleCharacterData::Import()
{
#if WITH_EDITORONLY_DATA
	if (!DataTable ||
		!DataTable->GetRowStruct()->IsChildOf(FCharacterData::StaticStruct()))
	{
		return;
	}

	// �f�[�^�����Z�b�g
	Data.Empty();

	// �f�[�^�̍s�����擾
	auto Names = DataTable->GetRowNames();

	// �f�[�^�̎擾
	for (int i = 0; i < Names.Num(); i++)
	{
		// �f�[�^�̒��o
		auto record = DataTable->FindRow<FCharacterData>(Names[i], FString());

		// �l�̐ݒ�
		FCharacterDataAssetRecord asset;
		asset.MyTeam = record->MyTeam;
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
