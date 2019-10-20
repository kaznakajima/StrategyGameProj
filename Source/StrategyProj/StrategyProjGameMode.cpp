// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StrategyProjGameMode.h"
#include "StrategyProjCharacter.h"
#include "GameFramework/Actor.h"
#include "BattleCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

AStrategyProjGameMode::AStrategyProjGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// 戦闘準備
void AStrategyProjGameMode::BattleCharacterSetting(AActor* _Player, AActor* _Enemy)
{
	// 先攻、後攻の設定
	FirstCharacter = Cast<ABattleCharacter>(_Player);
	LateCharacter = Cast<ABattleCharacter>(_Enemy);

	// 戦闘ステージにフォーカス
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	MyController->SetViewTargetWithBlend(FirstCharacter, 0.0f);
	
	// Playerの設定
	FVector PlayerLocation = BattleStage->GetActorLocation() + FVector(-200.0f, 0.0f, 100.0f);
	_Player->SetActorLocation(PlayerLocation);

	// Enemyの設定
	FVector EnemyLocation = BattleStage->GetActorLocation() + FVector(200.0f, 0.0f, 100.0f);
	_Enemy->SetActorLocation(EnemyLocation);

	// 向かい合わせる
	FRotator PlayerRotate = UKismetMathLibrary::FindLookAtRotation(_Player->GetActorLocation(), _Enemy->GetActorLocation());
	_Player->SetActorRotation(PlayerRotate);
	FRotator EnemyRotate = UKismetMathLibrary::FindLookAtRotation(_Enemy->GetActorLocation(), _Player->GetActorLocation());
	_Enemy->SetActorRotation(EnemyRotate);

	// CaptureCameraで撮影
	BattleStage->Capture();
}

// 戦闘終了
void AStrategyProjGameMode::BattleEnd(ABattleCharacter * _Player, ABattleCharacter * _Enemy)
{
	_Player->SetActorLocation(_Player->MyLocation);
	_Enemy->SetActorLocation(_Enemy->MyLocation);

	// 向かい合わせる
	FRotator PlayerRotate = UKismetMathLibrary::FindLookAtRotation(_Player->GetActorLocation(), _Enemy->GetActorLocation());
	_Player->SetActorRotation(PlayerRotate);
	FRotator EnemyRotate = UKismetMathLibrary::FindLookAtRotation(_Enemy->GetActorLocation(), _Player->GetActorLocation());
	_Enemy->SetActorRotation(EnemyRotate);
}
