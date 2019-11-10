// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleCharacter.h"
#include "CharacterAIController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// ��]�̒�`
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// CharacterMovement�̃Z�b�g�A�b�v
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// SpringArm�̃Z�b�g�A�b�v
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera�̃Z�b�g�A�b�v
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// SceneCapture2DComponent�̃Z�b�g�A�b�v
	CaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCamera"));
	CaptureCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// �X�e�[�^�X�̏�����
void ABattleCharacter::InitializeStatus(FName _RowName)
{
	// �f�[�^�̒��o
	auto record = DataTable->FindRow<FCharacterData>(_RowName, FString());

	// �l�̐ݒ�
	MyStatus.MyTeam = record->MyTeam;
	MyStatus.EquipState = record->EquipState;
	MyStatus.BattleState = record->BattleState;
	MyStatus.Name = record->Name;
	MyStatus.MaxHP = record->MaxHP;
	CurrentHP = MyStatus.MaxHP;
	MyStatus.MaxSP = record->MaxSP;
	CurrentSP = MyStatus.MaxSP;
	MyStatus.STR = record->Power;
	MyStatus.DEF = record->Defence;
	MyStatus.AVO = record->Avoid;
}

// �_���[�W�C�x���g
void ABattleCharacter::OnDamage_Implementation(float MagicPower, AActor * _actor, float _def)
{
	AController* PlayerController = GetController();

	// �_���[�W�v�Z
	float damage = (MyStatus.STR + MagicPower) - _def;

	// �_���[�W�C�x���g�̎擾
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	// �_���[�W����
	_actor->TakeDamage(damage, DamageEvent, PlayerController, this);
}

// �R���W�����L����
void ABattleCharacter::OnUseCollision_Implementation(UPrimitiveComponent * Col)
{
	// �R���W���������݂���Ȃ�L����
	if (Col != nullptr) Col->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// �R���W����������
void ABattleCharacter::OnUnUseCollision_Implementation(UPrimitiveComponent * Col_1, UPrimitiveComponent * Col_2)
{
	// �R���W���������݂���Ȃ疳����
	if (Col_1 != nullptr) Col_1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Col_2 != nullptr)Col_2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// �������v���C���[�̃`�[�����ǂ����Ԃ�
bool ABattleCharacter::GetIsPlayerTeam()
{
	// �v���C���[�`�[���Ȃ� true
	if (MyStatus.MyTeam == ECharacterTeam::Team1) return true;

	return false;
}

// ������Ԃ�Ԃ�
EEquipmentState ABattleCharacter::GetEquipState()
{
	return MyStatus.EquipState;
}

// �퓬��Ԃ�Ԃ�
EBattleState ABattleCharacter::GetBattleState()
{
	return MyStatus.BattleState;
}

// ���񏈗�
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// �����̎��s
void ABattleCharacter::EquipActive(UStaticMeshComponent * _EquipMesh, UStaticMeshComponent* _TargetMesh, FTransform _EquipTransform)
{
	// �����ʒu�Ɉړ�
	_TargetMesh->SetStaticMesh(_EquipMesh->GetStaticMesh());
	_TargetMesh->SetRelativeTransform(_EquipTransform);
}

// ������Ԃ̐ݒ�
void ABattleCharacter::EquipSetting(EEquipmentState _State, FWeaponStatus _Status)
{
	MyStatus.EquipState = _State;

	// �X�e�[�^�X�X�V
	MyStatus.MaxHP = MyStatus.MaxHP + _Status.HP;
	MyStatus.MaxSP = MyStatus.MaxSP + _Status.SP;
	MyStatus.STR = MyStatus.STR + _Status.STR;
	MyStatus.DEF = MyStatus.DEF + _Status.DEF;
	MyStatus.AVO = MyStatus.AVO + _Status.AVO;

	EquipEvent.Broadcast(MyStatus.EquipState);
}

// �퓬�X�e�[�g�̐ݒ�
void ABattleCharacter::BattleSetting(EBattleState _State)
{
	MyStatus.BattleState = _State;
}

// �L�����N�^�[�̈ړ�
void ABattleCharacter::NextMove(AActor* _TargetActor, float _Range)
{
	// ���g��Controller�̎擾
	ACharacterAIController* MyController = Cast<ACharacterAIController>(GetController());

	// �^�[�Q�b�g�����Ɉړ�
	if (MyController != nullptr && Moving == false) {
		MyController->MoveToActor(_TargetActor, _Range, false);
		Moving = true;
	}
}

// ���̒n�_�ɖ߂�
void ABattleCharacter::ResetMove(FVector _OffsetLocation, float _Range)
{
	// ���g��Controller�̎擾
	ACharacterAIController* MyController = Cast<ACharacterAIController>(GetController());

	FVector TargetLocation = GetActorLocation() + _OffsetLocation;

	// �^�[�Q�b�g�����Ɉړ�
	if (MyController != nullptr) {
		MyController->MoveToLocation(TargetLocation, _Range, false);
		GetCharacterMovement()->bOrientRotationToMovement = false;
		Moving = false;
	}
}

// ����]
void ABattleCharacter::TurnAtRate(float _Rate)
{
	AddControllerYawInput(_Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
// �c��]
void ABattleCharacter::LookUpAtRate(float _Rate)
{
	AddControllerPitchInput(_Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// �v���C���[�ړ�
void ABattleCharacter::PlayerMove(AActor* _TargetActor, float _Value)
{
	// �ړ����̓��^�[��
	if (Moving) return;

	NextMove(_TargetActor, 50.0f);
}

// Called every frame
void ABattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// �J������]
	PlayerInputComponent->BindAxis("Turn", this, &ABattleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ABattleCharacter::LookUpAtRate);
}

