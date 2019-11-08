// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerControllPawn::APlayerControllPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// SceneComponent�̃Z�b�g�A�b�v
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);

	// SpringArm�̃Z�b�g�A�b�v
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(DefaultSceneComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera�̃Z�b�g�A�b�v
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// ���񏈗�
void APlayerControllPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// ���Ɉړ�����L�����N�^�[��\��
ABattleCharacter * APlayerControllPawn::GetNextCharacter()
{
	// �e�L�����N�^�[������
	for (ABattleCharacter* Character : CharacterList) {
		if (Character->Moving == false) return Character;
	}

	return nullptr;
}

// �J������]
void APlayerControllPawn::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerControllPawn::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// �X�V����
void APlayerControllPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// �C���v�b�g�̃Z�b�g�A�b�v
void APlayerControllPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerControllPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerControllPawn::LookUpAtRate);
}

