// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterInterface.h"
#include "Components/StaticMeshComponent.h"
#include "BattleCharacter.generated.h"

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

protected:

	// �L�����N�^�[�̑������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	EEquipmentState MyState;

	// �L�����N�^�[�̃X�e�[�^�X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	FCharacterStatus MyStatus;

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
	void EquipActive(UStaticMeshComponent* _EquipMesh, UStaticMeshComponent* _TargetMesh);

	// �L�����N�^�[�̈ړ�
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
	void NextMove(FVector _MoveVec);

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	// �J�����ړ�
	void TurnAtRate(float Rate);
	// �J�����ړ�
	void LookUpAtRate(float Rate);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// ���Վ��_���ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	bool BottomView;

	// �ړ��������ǂ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	bool Moving;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SpringArm�̎擾
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Camera�̎擾
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
