// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAIController.h"
#include "BattleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// 移動完了後の処理
void ACharacterAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	// 操作中のキャラクターの取得
	ABattleCharacter* MyCharacter = Cast<ABattleCharacter>(GetPawn());

	// 移動完了したらフラグを立てる
	if (MyCharacter != nullptr && MyCharacter->Moving) {
		if (MyCharacter->IsBattle) {
			MyCharacter->ActionEvent();
			return;
		}

		MyCharacter->MyLocation = MyCharacter->GetActorLocation();
		MyCharacter->MoveEndEvent.Broadcast(false);
	}
	else if(MyCharacter != nullptr && MyCharacter->IsBattle == false) {
		// アクション終了
		MyCharacter->ActionEnd();
		MyCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}
