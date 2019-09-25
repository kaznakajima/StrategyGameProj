// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomData.h"

// Sets default values
ARoomData::ARoomData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// 初期化
void ARoomData::Init(int _ID, int _x, int _y, int _width, int _height)
{
	// 部屋のステータス定義
	MyStatus.AreaID = _ID;
	OwnerTop = _y;
	OwnerLeft = _x;
	
	MyStatus.RoomWidth = _width - 2;
	MyStatus.RoomHeight = _height - 2;
}

// 部屋の情報定義
void ARoomData::InitializeRoom()
{
	// エリア位置から部屋の生成位置を定義していく
	MyStatus.Top = OwnerTop;
	MyStatus.Bottom = MyStatus.Top + MyStatus.RoomHeight;
	MyStatus.Left = OwnerLeft;
	MyStatus.Right = MyStatus.Left + MyStatus.RoomWidth;

	CreateRoom();
}

// 部屋の生成
void ARoomData::CreateRoom()
{
	// 部屋用のアクターの準備
	FString path = "/Game/MyRoomActor.MyRoomActor_C"; 
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	// マップ生成
	// 生成位置
	FVector SpawnPos = FVector(MyStatus.Left, MyStatus.Top, 0);
	FVector SpawnScale = FVector(MyStatus.RoomWidth, MyStatus.RoomHeight, 0.2);
	// 足場の生成
	AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
	StageChip->SetActorLocation(SpawnPos);
	StageChip->SetActorScale3D(SpawnScale);
	StageChip->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	MyRoom = Cast<ARoomActor>(StageChip);
}

// 通路の生成
void ARoomData::CreateRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom)
{
	_MyRoom->ConnectRoom(_MyRoom, _OpponentRoom);
}

// 孤立しないよう調節
void ARoomData::ConnectRoad(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// つないでいく
	if (_OpponentRoom->ConnectRoomList.Num() == 1) {
		_MyRoom->RemainderConnect(_MyRoom, _OpponentRoom);
	}
}

// 部屋がつながっているかチェック
void ARoomData::CheckRoomConnect()
{
}

// Called when the game starts or when spawned
void ARoomData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

