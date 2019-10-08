// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StrategyProjGameMode.generated.h"

UCLASS(minimalapi)
class AStrategyProjGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStrategyProjGameMode();

	// �퓬���邩�ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		bool BattleFlg;

	// �퓬����
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattlePrepare(AActor* _BattleField, AActor* _Player, AActor* _Enemy);

	// �퓬�I��
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleEnd(ABattleCharacter* _Player, ABattleCharacter* _Enemy);
};



