// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponData.h"

// �f�[�^���C���|�[�g����
void UWeaponData::Import()
{
#if WITH_EDITORONLY_DATA
	if (!DataTable ||
		!DataTable->GetRowStruct()->IsChildOf(FWeaponStatusData::StaticStruct()))
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
		auto record = DataTable->FindRow<FWeaponStatusData>(Names[i], FString());

		// �l�̐ݒ�
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
