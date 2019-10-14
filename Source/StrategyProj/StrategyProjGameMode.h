// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleStage.h"
#include "StrategyProjGameMode.generated.h"

UCLASS(minimalapi)
class AStrategyProjGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStrategyProjGameMode();

	// 戦闘するかどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		bool BattleFlg;

	// バトル用ステージ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		ABattleStage* BattleStage;

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



