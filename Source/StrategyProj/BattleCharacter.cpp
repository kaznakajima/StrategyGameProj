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

	// 回転の定義
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// CharacterMovementのセットアップ
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// SpringArmのセットアップ
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Cameraのセットアップ
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// SceneCapture2DComponentのセットアップ
	CaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCamera"));
	CaptureCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// ステータスの初期化
void ABattleCharacter::InitializeStatus(FName _RowName)
{
	// データの抽出
	auto record = DataTable->FindRow<FCharacterData>(_RowName, FString());

	// 値の設定
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

// ダメージイベント
void ABattleCharacter::OnDamage_Implementation(float MagicPower, AActor * _actor, float _def)
{
	AController* PlayerController = GetController();

	// ダメージ計算
	float damage = (MyStatus.STR + MagicPower) - _def;

	// ダメージイベントの取得
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	// ダメージ処理
	_actor->TakeDamage(damage, DamageEvent, PlayerController, this);
}

// コリジョン有効化
void ABattleCharacter::OnUseCollision_Implementation(UPrimitiveComponent * Col)
{
	// コリジョンが存在するなら有効化
	if (Col != nullptr) Col->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// コリジョン無効化
void ABattleCharacter::OnUnUseCollision_Implementation(UPrimitiveComponent * Col_1, UPrimitiveComponent * Col_2)
{
	// コリジョンが存在するなら無効化
	if (Col_1 != nullptr) Col_1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Col_2 != nullptr)Col_2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// 自分がプレイヤーのチームかどうか返す
bool ABattleCharacter::GetIsPlayerTeam()
{
	// プレイヤーチームなら true
	if (MyStatus.MyTeam == ECharacterTeam::Team1) return true;

	return false;
}

// 装備状態を返す
EEquipmentState ABattleCharacter::GetEquipState()
{
	return MyStatus.EquipState;
}

// 戦闘状態を返す
EBattleState ABattleCharacter::GetBattleState()
{
	return MyStatus.BattleState;
}

// 初回処理
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// 装備の実行
void ABattleCharacter::EquipActive(UStaticMeshComponent * _EquipMesh, UStaticMeshComponent* _TargetMesh, FTransform _EquipTransform)
{
	// 装備位置に移動
	_TargetMesh->SetStaticMesh(_EquipMesh->GetStaticMesh());
	_TargetMesh->SetRelativeTransform(_EquipTransform);
}

// 装備状態の設定
void ABattleCharacter::EquipSetting(EEquipmentState _State)
{
	MyStatus.EquipState = _State;
}

// 戦闘ステートの設定
void ABattleCharacter::BattleSetting(EBattleState _State)
{
	MyStatus.BattleState = _State;
}

// キャラクターの移動
void ABattleCharacter::NextMove(AActor* _TargetActor, float _Range)
{
	// 自身のControllerの取得
	ACharacterAIController* MyController = Cast<ACharacterAIController>(GetController());

	// ターゲット方向に移動
	if (MyController != nullptr && Moving == false) {
		MyController->MoveToActor(_TargetActor, _Range, false);
		Moving = true;
	}
}

// 元の地点に戻る
void ABattleCharacter::ResetMove(FVector _OffsetLocation, float _Range)
{
	// 自身のControllerの取得
	ACharacterAIController* MyController = Cast<ACharacterAIController>(GetController());

	FVector TargetLocation = GetActorLocation() + _OffsetLocation;

	// ターゲット方向に移動
	if (MyController != nullptr && Moving == false) {
		MyController->MoveToLocation(TargetLocation, _Range, false);
		Moving = false;
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

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABattleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABattleCharacter::LookUpAtRate);
}

