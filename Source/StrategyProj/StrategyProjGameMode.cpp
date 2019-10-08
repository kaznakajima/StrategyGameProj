// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StrategyProjGameMode.h"
#include "StrategyProjCharacter.h"
#include "GameFramework/Actor.h"
#include "BattleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AStrategyProjGameMode::AStrategyProjGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// �퓬����
void AStrategyProjGameMode::BattlePrepare(AActor* _BattleField, AActor* _Player, AActor* _Enemy)
{
	// �퓬�X�e�[�W�Ƀt�H�[�J�X
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	MyController->SetViewTargetWithBlend(_BattleField, 1.0f);

	FVector PlayerLocation = _BattleField->GetActorLocation() + FVector(80.0f, 0.0f, 100.0f);
	_Player->SetActorLocation(PlayerLocation);
	FVector EnemyLocation = _BattleField->GetActorLocation() + FVector(-80.0f, 0.0f, 100.0f);
	_Enemy->SetActorLocation(EnemyLocation);

	BattleFlg = true;
}

// �퓬�I��
void AStrategyProjGameMode::BattleEnd(ABattleCharacter * _Player, ABattleCharacter * _Enemy)
{
	_Player->SetActorLocation(_Player->MyLocation);
	_Enemy->SetActorLocation(_Enemy->MyLocation);
}
