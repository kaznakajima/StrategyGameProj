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
enum class ECharacterTeam : uint8
{
	Team1		UMETA(DisplayName = "PlayerTeam"),
	Team2		UMETA(DisplayName = "EnemyTeam")
};

// �L�����N�^�[�̑������
UENUM(BlueprintType)
enum class EEquipmentState : uint8
{
	NONE = 0							UMETA(DisplayName = "NONE"),
	SWORD = 1						UMETA(DisplayName = "SWORD"),
	DOUBLE_SWORD = 2			UMETA(DisplayName = "DOUBLE_SWORD"),
	TWOHAND_SWORD = 4		UMETA(DisplayName = "TWOHAND_SWORD"),
	SHILD = 8							UMETA(DisplayName = "SHILD"),
	SWORD_SHILD = 16			UMETA(DisplayName = "SWORD_SHILD"),
	MAGICWAND = 32				UMETA(DisplayName = "MAGICWAND"),
	BOW = 64							UMETA(DisplayName = "BOW"),
};

// �퓬���̃A�N�V����
UENUM(BlueprintType)
enum class EBattleState : uint8
{
	NONE			UMETA(DisplayName = "NONE"),
	ATTACK			UMETA(DisplayName = "ATTACK"),
	GARD			UMETA(DisplayNama = "GARD"),
	AVOID			UMETA(DisplayName = "AVOID"),
	SKILL			UMETA(DisplayName = "SKILL"),
};

// �L�����N�^�[�X�e�[�^�X
USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_USTRUCT_BODY()

	// �����`�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ECharacterTeam MyTeam;

	// �L�����N�^�[�̑������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EEquipmentState EquipState;

	// �L�����N�^�[�̑������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		EBattleState BattleState;

	// �L�����N�^�[��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FText Name;

	// HP(�̗�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float MaxHP;

	// SP(�X�L���|�C���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float MaxSP;

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
	// �R���W�����L����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceAction")
		void OnUseCollision(class UPrimitiveComponent* Col);

	// �R���W����������
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceAction")
		void OnUnUseCollision(class UPrimitiveComponent* Col_1, class UPrimitiveComponent* Col_2);

	// �_���[�W����
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InterfaceAction")
		void OnDamage(float MagicPower, AActor* actor, float defence);

	// ���S�C�x���g
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
		void DeathAction();

};
