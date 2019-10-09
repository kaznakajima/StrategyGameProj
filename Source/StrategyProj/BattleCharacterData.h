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

	// �����`�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

	// �L�����N�^�[�̑������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EEquipmentState MyState;

	// �L�����N�^�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FText Name;

	// HP(�̗�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int MaxHP;

	// SP(�X�L���|�C���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int MaxSP;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Power;

	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Defence;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Avoid;
};

USTRUCT(BlueprintType)
struct FCharacterDataAssetRecord
{
	GENERATED_USTRUCT_BODY()
public:

	// �����`�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

	// �L�����N�^�[�̑������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EEquipmentState MyState;

	// �L�����N�^�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FText Name;

	// HP(�̗�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int MaxHP;

	// SP(�X�L���|�C���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int MaxSP;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Power;

	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Defence;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int Avoid;
};

// �퓬�p�L�����N�^�[�̃X�e�[�^�X�f�[�^
UCLASS()
class STRATEGYPROJ_API UBattleCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	// �f�[�^�e�[�u��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditData")
		UDataTable* DataTable;
#endif
	// �e�[�u�����C���|�[�g����
	UFUNCTION(meta = (CallInEditor = "true"))
		void Import();

	// �f�[�^���X�g
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FCharacterDataAssetRecord> Data;
};
