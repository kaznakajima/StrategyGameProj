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

	// HP(�̗�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SP(�X�L���|�C���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int STR;

	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int DEF;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int AVO;
};

USTRUCT(BlueprintType)
struct FWeaponStatusData
{
	GENERATED_USTRUCT_BODY()

public:

	// HP(�̗�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int HP;

	// SP(�X�L���|�C���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int SP;

	// �U����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int STR;

	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int DEF;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		int AVO;
};

UCLASS()
class STRATEGYPROJ_API UWeaponData : public UDataAsset
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
		TArray<FWeaponStatusData> Data;
};
