
#include "BattleStage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABattleStage::ABattleStage()
{
	// Tick������
	PrimaryActorTick.bCanEverTick = true;

	// Root�̃Z�b�g�A�b�v
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	// SpringArm�̃Z�b�g�A�b�v
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera�̃Z�b�g�A�b�v
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// MainTile�̃Z�b�g�A�b�v
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

