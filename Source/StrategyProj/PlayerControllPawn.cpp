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

	// SceneComponentのセットアップ
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComponent"));
	DefaultSceneComponent->SetupAttachment(RootComponent);

	// SpringArmのセットアップ
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(DefaultSceneComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Cameraのセットアップ
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// 初回処理
void APlayerControllPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// 次に移動するキャラクターを表示
ABattleCharacter * APlayerControllPawn::GetNextCharacter()
{
	// 各キャラクターを検索
	for (ABattleCharacter* Character : CharacterList) {
		if (Character->Moving == false) return Character;
	}

	return nullptr;
}

// カメラ回転
void APlayerControllPawn::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerControllPawn::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// 更新処理
void APlayerControllPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// インプットのセットアップ
void APlayerControllPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerControllPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerControllPawn::LookUpAtRate);
}

