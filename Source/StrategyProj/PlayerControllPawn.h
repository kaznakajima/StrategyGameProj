// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleCharacter.h"
#include "MapCreate.h"
#include "PlayerControllPawn.generated.h"

UCLASS()
class STRATEGYPROJ_API APlayerControllPawn : public APawn
{
	GENERATED_BODY()

	// SceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneComponent;
	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

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

	// MapCreate�̎Q��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Map")
		AMapCreate* MainMap;

	// ���Վ��_���ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
		bool IsView;
	// ���Վ��_���̃X�e�[�W�̒��ԍ��W
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
		FVector ViewLocation;
	// ���_���[�h�ύX
	UFUNCTION(BlueprintCallable, Category = "Character")
		void ChangeViewMode();

	// ���݃A�N�e�B�u(�I��)�ȃL�����N�^�[
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
		ABattleCharacter* ActiveCharacter;
	// ���Ɉړ�����L�����N�^�[���擾
	UFUNCTION(BlueprintCallable, Category = "Character")
		ABattleCharacter* GetNextCharacter();

	// �J�����̉�]��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	
	// �J�����̉�]��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// �J�����ړ�
	void TurnAtRate(float Rate);
	// �J�����ړ�
	void LookUpAtRate(float Rate);

public:	
	// �X�V����
	virtual void Tick(float DeltaTime) override;

	// �C���v�b�g�̃Z�b�g�A�b�v
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SceneComponent�̎擾
	FORCEINLINE class USceneComponent* GetSceneComponent() const { return DefaultSceneComponent; }
	// SpringArm�̎擾
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Camera�̎擾
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
