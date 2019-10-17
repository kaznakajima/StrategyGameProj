// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterInterface.h"
#include "Components/StaticMeshComponent.h"
#include "RoomActor.h"
#include "BattleCharacterData.h"
#include "BattleCharacter.generated.h"

// ���I�}���`�L���X�g�f���Q�[�g(�C�x���g�f�B�X�p�b�`���[)�̐錾
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterMoveEvent, bool, IsCancel);

// �퓬���s���L�����N�^�[�N���X
UCLASS()
class STRATEGYPROJ_API ABattleCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	// �R���X�g���N�^
	ABattleCharacter();

	// SceneCapture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneCaptureComponent2D* CaptureCamera;

	// EventDispatcher(�ړ��I���C�x���g)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FCharacterMoveEvent MoveEndEvent;

	// �X�e�[�^�X�̏�����
	UFUNCTION(BlueprintCallable, Category = "Character")
		void InitializeStatus(FName _RowName);

	// �_���[�W�C�x���g
	void OnDamage_Implementation(AActor* actor, float defence) override;

	// �R���W�����L����
	void OnUseCollision_Implementation(class UPrimitiveComponent* Col) override;

	// �R���W����������
	void OnUnUseCollision_Implementation(class UPrimitiveComponent* Col_1, class UPrimitiveComponent* Col_2) override;

	// ���g�̕����ł̗����ʒu
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FVector MyLocation;

	// �ΐ킷��G�L�����N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		ABattleCharacter* BattleEnemy;

	// �������v���C���[�̃`�[�����ǂ���
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		bool GetIsPlayerTeam();

	// ���݂̑�����Ԃ�Ԃ�
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		EEquipmentState GetEquipState();
	// ���݂̑�����Ԃ�Ԃ�
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		EBattleState GetBattleState();

	// �o�g�������ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		bool IsBattle;

protected:

	// �f�[�^�e�[�u��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditData")
		UDataTable* DataTable;

	// �L�����N�^�[�̃X�e�[�^�X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FCharacterStatus MyStatus;
	// ���݂�HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float CurrentHP;
	// ���݂�SP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float CurrentSP;

	// ���g�̂��镔��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ARoomActor* CurrentRoom;

	// �J�����̉�]��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	// �J�����̉�]��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Debug�p(�̂��ɍ폜)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
		bool IsDebug;

	// ����
	UFUNCTION(BlueprintCallable, Category = "Equip")
		void EquipActive(UStaticMeshComponent* _EquipMesh, UStaticMeshComponent* _TargetMesh, FTransform _EquipTransform);
	// ������Ԃ̐ݒ�
	UFUNCTION(BlueprintCallable, Category = "Equip")
		void EquipSetting(EEquipmentState _State);

	// �퓬�X�e�[�g�̐ݒ�
	UFUNCTION(BlueprintCallable, Category = "Equip")
		void BattleSetting(EBattleState _State);

	// �L�����N�^�[�̈ړ�
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
		void NextMove(AActor* _TargetActor, float _Range);

		void MoveForward(float Value);

		void MoveRight(float Value);
	
	// �J�����ړ�
		void TurnAtRate(float Rate);
	// �J�����ړ�
		void LookUpAtRate(float Rate);

	// ���񎞂̏���
		virtual void BeginPlay() override;

public:

	// ���Վ��_���ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		bool BottomView;

	// �ړ��������ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		bool Moving;

	// �ړ��L�����Z���C�x���g
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void MoveCancel();

	// �퓬�����C�x���g
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void BattlePrepare();

	// �퓬�C�x���g
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void ActionEvent();

	// �퓬�A�N�V�����J�n�C�x���g
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void ActionMove();

	// �X�V����
		virtual void Tick(float DeltaTime) override;

	// �C���v�b�g�̃Z�b�g�A�b�v
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SpringArm�̎擾
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Camera�̎擾
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// SceneCapture�̎擾
	FORCEINLINE class USceneCaptureComponent2D* GetCaptureCamera() const { return CaptureCamera; }
};
