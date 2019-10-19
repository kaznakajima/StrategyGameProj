// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleStage.h"
#include "StrategyProjGameMode.generated.h"

// ���I�}���`�L���X�g�f���Q�[�g(�C�x���g�f�B�X�p�b�`���[)�̐錾
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBattleEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirstCharacterEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLateCharacterEvent);

UCLASS(minimalapi)
class AStrategyProjGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStrategyProjGameMode();

	// �퓬���邩�ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		bool BattleFlg;

	// �퓬�J�n�C�x���g
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FBattleStart BattleStartEvent;
	// �퓬�I���C�x���g
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FBattleEnd BattleEndEvent;

	// EventDispatcher(��U�L�����N�^�[�C�x���g)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FFirstCharacterEvent FirstCharacterEvent;
	// EventDispatcher(��U�L�����N�^�[�C�x���g)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FLateCharacterEvent LateCharacterEvent;

	// �o�g���p�X�e�[�W
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		ABattleStage* BattleStage;

	// ��U�̃L�����N�^�[
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		ABattleCharacter* FirstCharacter;

	// ��U�̃L�����N�^�[
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		ABattleCharacter* LateCharacter;

	// �퓬����
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleCharacterSetting(AActor* _Player, AActor* _Enemy);

	// �퓬�I��
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleEnd(ABattleCharacter* _Player, ABattleCharacter* _Enemy);

	// UI�����C�x���g
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void BattleUICreate();
};



