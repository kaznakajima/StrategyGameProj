// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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

// ���_�̕ύX
void APlayerControllPawn::ChangeViewMode()
{
	// MapCreate���i�[����Ă��Ȃ��ꍇ���s
	if (MainMap == nullptr) {
		// MapCreate��T��
		TSubclassOf<AMapCreate> findClass;
		findClass = AMapCreate::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, actors);

		// �T���������ʂ��i�[
		MainMap = Cast<AMapCreate>(actors[0]);
	}

	// ���Ղ���L�����N�^�[���_��
	if (IsView) {
		IsView = false;
	}
	// ���Վ��_��
	else {
		// �����̐����璆�Ԃ��擾
		int Count = (MainMap->MyStatus.RoomCount - 1) * 0.5f;
		// ���Ԓn�_�̍��W�_���v�Z
		float ViewPosition = (MainMap->MyStatus.AreaSize * Count) * 100.0f;
		// �ړ�����
		ViewLocation = FVector(ViewPosition, ViewPosition, 5000.0f);

		IsView = true;
	}
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

