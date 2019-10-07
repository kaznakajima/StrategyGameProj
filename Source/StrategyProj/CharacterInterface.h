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

// �L�����N�^�[�̑������
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

// �L�����N�^�[�X�e�[�^�X
USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_USTRUCT_BODY()

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
	int STR;

	// �h���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int DEF;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	int AVO;
};

// �L�����N�^�[�C���^�[�t�F�C�X
class STRATEGYPROJ_API ICharacterInterface
{
	GENERATED_IINTERFACE_BODY()

public:

};
