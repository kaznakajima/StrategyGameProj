// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleCharacter.h"
#include "CharacterAIController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
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
	MyStatus.MyState = record->MyState;
	MyStatus.Name = record->Name;
	MyStatus.MaxHP = record->MaxHP;
	MyStatus.MaxSP = record->MaxSP;
	MyStatus.STR = record->Power;
	MyStatus.DEF = record->Defence;
	MyStatus.AVO = record->Avoid;
}

// �������v���C���[�̃`�[�����ǂ����Ԃ�
bool ABattleCharacter::GetIsPlayerTeam()
{
	// �v���C���[�`�[���Ȃ� true
	if (MyStatus.MyTeam == ECharacterTeam::Team1) return true;

	return false;
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

// �L�����N�^�[�̈ړ�
void ABattleCharacter::NextMove(AActor* _TargetActor, float _Range)
{
	// ���g��Controller�̎擾
	ACharacterAIController* MyController = Cast<ACharacterAIController>(GetController());

	// �ړ�
	if (MyController != nullptr && Moving == false) {
		MyController->MoveToActor(_TargetActor, _Range, false);
		Moving = true;
	}
}

void ABattleCharacter::MoveForward(float Value)
{
	if (IsDebug == false) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABattleCharacter::MoveRight(float Value)
{
	if (IsDebug == false) return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABattleCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABattleCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABattleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABattleCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABattleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABattleCharacter::LookUpAtRate);
}

