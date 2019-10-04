// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomActor.h"

// コンストラクタ
ARoomActor::ARoomActor()
{
	// 大元のメッシュ
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	TileMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.2f));
	//------------------四方の通路を子にしていく------------------
	// 上
	Aisle_T_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_T"));
	Aisle_T_Mesh->SetupAttachment(TileMesh);
	Aisle_T_Mesh->SetRelativeLocation(FVector(0.0f, -67.0f, 0.0f));
	Aisle_T_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// 下
	Aisle_B_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_B"));
	Aisle_B_Mesh->SetupAttachment(TileMesh);
	Aisle_B_Mesh->SetRelativeLocation(FVector(0.0f, 67.0f, 0.0f));
	Aisle_B_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// 左
	Aisle_L_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_L"));
	Aisle_L_Mesh->SetupAttachment(TileMesh);
	Aisle_L_Mesh->SetRelativeLocation(FVector(-67.0f, 0.0f, 0.0f));
	Aisle_L_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// 右
	Aisle_R_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_R"));
	Aisle_R_Mesh->SetupAttachment(TileMesh);
	Aisle_R_Mesh->SetRelativeLocation(FVector(67.0f, 0.0f, 0.0f));
	Aisle_R_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	//---------------------------------------------------------------

	// 移動目標地点のセットアップ
	MovePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MovePoint"));
	MovePoint->SetupAttachment(TileMesh);
	MovePoint->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));


 	// Tickを適用
	PrimaryActorTick.bCanEverTick = true;
}

// 部屋同士をつなぐ
void ARoomActor::ConnectRoom(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// 部屋同士の位置関係
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// 横通路
	if (DifferencePos.X < 0.0f) {
		// つなぐかどうかの乱数
		int IsConnect = FMath::RandRange(0, 100);

		// 通路を作る
		if (IsConnect > 49) {
			_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);
			_MyRoom->Aisle_R_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// 接続した部屋をリストに格納
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}

	// 縦通路
	if (DifferencePos.Y < 0.0f) {
		// つなぐかどうかの乱数
		int IsConnect = FMath::RandRange(0, 100);

		// 通路を作る
		if (IsConnect > 49) {
			_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);
			_MyRoom->Aisle_B_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// 接続した部屋をリストに格納
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

	// 部屋同士の位置関係
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// 横通路
	if (DifferencePos.X < 0.0f) {
		_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);
		_MyRoom->Aisle_R_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	// 縦通路
	if (DifferencePos.Y < 0.0f) {
		_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);
		_MyRoom->Aisle_B_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	// 部屋同士をつないでいく
	_MyRoom->ConnectRoomList.Add(_OpponentRoom);
	_OpponentRoom->ConnectRoomList.Add(_MyRoom);
}

// 部屋がつながっているかチェック
bool ARoomActor::CheckConnectRoom()
{
	// 部屋がつながっていないのなら削除
	if (ConnectRoomList.Num() == 0) {
		Destroy();
		return true;
	}
	else {
		RoomImitialize();
	}
	return false;
}

// 部屋の状態を初期化
void ARoomActor::RoomImitialize()
{
	FString path = "/Game/StageParts/RoomEffect.RoomEffect_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	// エフェクトの位置調整
	RoomEffect = GetWorld()->SpawnActor<AActor>(sc);
	RoomEffect->SetActorLocation(GetActorLocation());
	RoomEffect->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

// 初回処理
void ARoomActor::BeginPlay()
{

}

// 更新処理
void ARoomActor::Tick(float DeltaTime)
{
}

