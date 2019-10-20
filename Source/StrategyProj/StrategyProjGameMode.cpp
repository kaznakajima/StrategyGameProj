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

// �퓬����
void AStrategyProjGameMode::BattleCharacterSetting(AActor* _Player, AActor* _Enemy)
{
	// ��U�A��U�̐ݒ�
	FirstCharacter = Cast<ABattleCharacter>(_Player);
	LateCharacter = Cast<ABattleCharacter>(_Enemy);

	// �퓬�X�e�[�W�Ƀt�H�[�J�X
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	MyController->SetViewTargetWithBlend(FirstCharacter, 0.0f);
	
	// Player�̐ݒ�
	FVector PlayerLocation = BattleStage->GetActorLocation() + FVector(-200.0f, 0.0f, 100.0f);
	_Player->SetActorLocation(PlayerLocation);

	// Enemy�̐ݒ�
	FVector EnemyLocation = BattleStage->GetActorLocation() + FVector(200.0f, 0.0f, 100.0f);
	_Enemy->SetActorLocation(EnemyLocation);

	// ���������킹��
	FRotator PlayerRotate = UKismetMathLibrary::FindLookAtRotation(_Player->GetActorLocation(), _Enemy->GetActorLocation());
	_Player->SetActorRotation(PlayerRotate);
	FRotator EnemyRotate = UKismetMathLibrary::FindLookAtRotation(_Enemy->GetActorLocation(), _Player->GetActorLocation());
	_Enemy->SetActorRotation(EnemyRotate);

	// CaptureCamera�ŎB�e
	BattleStage->Capture();
}

// �퓬�I��
void AStrategyProjGameMode::BattleEnd(ABattleCharacter * _Player, ABattleCharacter * _Enemy)
{
	_Player->SetActorLocation(_Player->MyLocation);
	_Enemy->SetActorLocation(_Enemy->MyLocation);

	// ���������킹��
	FRotator PlayerRotate = UKismetMathLibrary::FindLookAtRotation(_Player->GetActorLocation(), _Enemy->GetActorLocation());
	_Player->SetActorRotation(PlayerRotate);
	FRotator EnemyRotate = UKismetMathLibrary::FindLookAtRotation(_Enemy->GetActorLocation(), _Player->GetActorLocation());
	_Enemy->SetActorRotation(EnemyRotate);
}
