
#include "BattleStage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABattleStage::ABattleStage()
{
	// Tickさせる
	PrimaryActorTick.bCanEverTick = true;

	// Rootのセットアップ
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	// SpringArmのセットアップ
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Cameraのセットアップ
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// MainTileのセットアップ
	MainTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainTile"));
	MainTile->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABattleStage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

