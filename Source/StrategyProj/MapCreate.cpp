// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreate.h"
#include "Kismet/GameplayStatics.h"
#include "BattleCharacter.h"

// コンストラクタ
AMapCreate::AMapCreate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// マップの生成
void AMapCreate::CreateMap()
{
	FString path = "/Game/StageParts/MyRoomData.MyRoomData_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();
	FVector SpawnPos = FVector::ZeroVector;
	// 部屋を作る
	for (int numY = 0; numY < MyStatus.RoomCount; numY++) {
		for (int numX = 0; numX < MyStatus.RoomCount; numX++) {
			// 生成位置の定義
			 SpawnPos = FVector(numX * (MyStatus.AreaSize * 100), numY * (MyStatus.AreaSize * 100), 0);
			// 部屋の設置
			ARoomData* NewRoom = GetWorld()->SpawnActor<ARoomData>(sc);
			NewRoom->Init(numY + numX, SpawnPos.X, SpawnPos.Y, MyStatus.AreaSize, MyStatus.AreaSize);
			NewRoom->SetActorLocation(SpawnPos);	// 位置調整
			NewRoom->InitializeRoom();						// 部屋の情報初期化
			AreaList.Add(NewRoom);							// リストに保存
		}
	}

	// 部屋同士をつないでいく
	for (int num = 0; num < MyStatus.RoomCount * MyStatus.RoomCount; num++) {
		// 横とつなぐ
		if ((num + 1) % MyStatus.RoomCount != 0) AreaList[num]->CreateRoad(AreaList[num]->MyRoom, AreaList[num + 1]->MyRoom);
		// 縦とつなぐ
		if (num < MyStatus.RoomCount * (MyStatus.RoomCount - 1)) {
			AreaList[num]->CreateRoad(AreaList[num]->MyRoom, AreaList[num + MyStatus.RoomCount]->MyRoom);
		}

		// 部屋がつながっていないなら削除
		if (AreaList[num]->MyRoom->CheckConnectRoom()) AreaList[num]->MyRoom = NULL;
	}

	// 部屋が孤立しないように調整
	for (int num = 0; num < MyStatus.RoomCount *  MyStatus.RoomCount - 1; num++) {
		// 部屋が削除されているならリターン
		if (AreaList[num]->MyRoom != nullptr) {
			if (AreaList[num + 1]->MyRoom != nullptr && (num + 1) % MyStatus.RoomCount != 0) AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + 1]->MyRoom);

			if (num < MyStatus.RoomCount * (MyStatus.RoomCount - 1) && AreaList[num + MyStatus.RoomCount]->MyRoom != nullptr) {
				AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + MyStatus.RoomCount]->MyRoom);
			}
		}
	}

	// つながっていない部屋を削除
	for (ARoomData* room : AreaList) {
		if (room->MyRoom == nullptr) AreaList.Remove(room);
	}

	for (int num = 0; num < MyStatus.UnitCount;num++) UnitSpawn();
}

// 領域の生成
void AMapCreate::CreateArea()
{

}

// 通路を生成
void AMapCreate::CreateRoad()
{

}

// ユニットの生成
void AMapCreate::UnitSpawn()
{
	FString path = "/Game/Character/MyBattleCharacter.MyBattleCharacter_C";
	TSubclassOf<class ABattleCharacter> character = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*path)).LoadSynchronous();

	int Index = FMath::RandRange(0, AreaList.Num() - 1);
	ABattleCharacter* Character = GetWorld()->SpawnActor<ABattleCharacter>(character);
	Character->SpawnDefaultController();
	FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
	Character->SetActorLocation(SpawnPos);
}

// Called when the game starts or when spawned
void AMapCreate::BeginPlay()
{
	CreateMap();
}

// Called every frame
void AMapCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

