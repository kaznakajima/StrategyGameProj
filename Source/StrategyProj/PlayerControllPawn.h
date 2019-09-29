// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleCharacter.h"
#include "PlayerControllPawn.generated.h"

UCLASS()
class STRATEGYPROJ_API APlayerControllPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerControllPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �L�����N�^�[�̃��X�g
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<ABattleCharacter*> CharacterList;
	// �L�����N�^�[���X�g�̃C���f�b�N�X�ԍ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	int Index;

	// ���݃A�N�e�B�u(�I��)�ȃL�����N�^�[
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	ABattleCharacter* ActiveCharacter;

	// ���Վ��_���ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	bool IsView;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
