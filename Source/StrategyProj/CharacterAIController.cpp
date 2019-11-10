// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAIController.h"
#include "BattleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// �ړ�������̏���
void ACharacterAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	// ���쒆�̃L�����N�^�[�̎擾
	ABattleCharacter* MyCharacter = Cast<ABattleCharacter>(GetPawn());

	// �ړ�����������t���O�𗧂Ă�
	if (MyCharacter != nullptr && MyCharacter->Moving) {
		if (MyCharacter->IsBattle) {
			MyCharacter->ActionEvent();
			return;
		}

		MyCharacter->MyLocation = MyCharacter->GetActorLocation();
		MyCharacter->MoveEndEvent.Broadcast(false);
	}
	else if(MyCharacter != nullptr && MyCharacter->IsBattle == false) {
		// �A�N�V�����I��
		MyCharacter->ActionEnd();
		MyCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}
