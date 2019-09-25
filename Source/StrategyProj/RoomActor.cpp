// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomActor.h"

// Sets default values
ARoomActor::ARoomActor()
{
	// メッシュの定義
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	TileMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.2f));
	// 四方の通路を子にしていく
	Aisle_T_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_T"));
	Aisle_T_Mesh->SetupAttachment(TileMesh);
	Aisle_T_Mesh->SetRelativeLocation(FVector(0.0f, -67.0f, 0.0f));
	Aisle_T_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	Aisle_B_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_B"));
	Aisle_B_Mesh->SetupAttachment(TileMesh);
	Aisle_B_Mesh->SetRelativeLocation(FVector(0.0f, 67.0f, 0.0f));
	Aisle_B_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	Aisle_L_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_L"));
	Aisle_L_Mesh->SetupAttachment(TileMesh);
	Aisle_L_Mesh->SetRelativeLocation(FVector(-67.0f, 0.0f, 0.0f));
	Aisle_L_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	Aisle_R_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_R"));
	Aisle_R_Mesh->SetupAttachment(TileMesh);
	Aisle_R_Mesh->SetRelativeLocation(FVector(67.0f, 0.0f, 0.0f));
	Aisle_R_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// 部屋同士をつなぐ
void ARoomActor::ConnectRoom(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// 部屋同士がつなげるかチェック
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();
	if (DifferencePos.X < 0.0f) {
		int IsConnect = FMath::RandRange(0, 100);

		if (IsConnect > 49) {
			_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);

			// 部屋同士をつないでいく
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}

	if (DifferencePos.Y < 0.0f) {
		int IsConnect = FMath::RandRange(0, 100);

		if (IsConnect > 49) {
			_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);

			// 部屋同士をつないでいく
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}
}

// 孤立しないように調整
void ARoomActor::RemainderConnect(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// 同じものは省く
	if (_MyRoom->ConnectRoomList.Contains(_OpponentRoom)) return;

	// 部屋同士がつなげるかチェック
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();
	if (DifferencePos.X < 0.0f) {
		_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);
	}

	if (DifferencePos.Y < 0.0f) {
		_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);
	}

	// 部屋同士をつないでいく
	_MyRoom->ConnectRoomList.Add(_OpponentRoom);
	_OpponentRoom->ConnectRoomList.Add(_MyRoom);
}

// 部屋がつながっているかチェック
void ARoomActor::CheckConnectRoom()
{
	if (ConnectRoomList.Num() == 0) {
		Destroy();
		EndPlay(EEndPlayReason::Type::Destroyed);
	}
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
}

