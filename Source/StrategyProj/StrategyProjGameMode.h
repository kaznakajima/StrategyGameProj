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

	// êÌì¨Ç∑ÇÈÇ©Ç«Ç§Ç©
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Battle")
		bool BattleFlg;

	// êÌì¨èÄîı
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattlePrepare(AActor* _BattleField, AActor* _Player, AActor* _Enemy);

	// êÌì¨èIóπ
	UFUNCTION(BlueprintCallable, Category = "Battle")
		void BattleEnd(ABattleCharacter* _Player, ABattleCharacter* _Enemy);
};



