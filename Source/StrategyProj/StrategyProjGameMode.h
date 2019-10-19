// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleStage.h"
#include "StrategyProjGameMode.generated.h"

// 動的マルチキャストデリゲート(イベントディスパッチャー)の宣言
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

	// 戦闘するかどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		bool BattleFlg;

	// 戦闘開始イベント
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FBattleStart BattleStartEvent;
	// 戦闘終了イベント
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FBattleEnd BattleEndEvent;

	// EventDispatcher(先攻キャラクターイベント)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FFirstCharacterEvent FirstCharacterEvent;
	// EventDispatcher(後攻キャラクターイベント)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FLateCharacterEvent LateCharacterEvent;

	// バトル用ステージ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		ABattleStage* BattleStage;

	// 先攻のキャラクター
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		ABattleCharacter* FirstCharacter;

	// 後攻のキャラクター
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		ABattleCharacter* LateCharacter;

	// 戦闘準備
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleCharacterSetting(AActor* _Player, AActor* _Enemy);

	// 戦闘終了
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleEnd(ABattleCharacter* _Player, ABattleCharacter* _Enemy);

	// UI生成イベント
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void BattleUICreate();
};



