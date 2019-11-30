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

// 視点の変更
void APlayerControllPawn::ChangeViewMode()
{
	// MapCreateが格納されていない場合実行
	if (MainMap == nullptr) {
		// MapCreateを探索
		TSubclassOf<AMapCreate> findClass;
		findClass = AMapCreate::StaticClass();
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, actors);

		// 探索した結果を格納
		MainMap = Cast<AMapCreate>(actors[0]);
	}

	// 俯瞰からキャラクター視点へ
	if (IsView) {
		IsView = false;
	}
	// 俯瞰視点へ
	else {
		// 部屋の数から中間を取得
		int Count = (MainMap->MyStatus.RoomCount - 1) * 0.5f;
		// 中間地点の座標点を計算
		float ViewPosition = (MainMap->MyStatus.AreaSize * Count) * 100.0f;
		// 移動方向
		ViewLocation = FVector(ViewPosition, ViewPosition, 5000.0f);

		IsView = true;
	}
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

