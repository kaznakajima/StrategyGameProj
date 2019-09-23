// Fill out your copyright notice in the Description page of Project Settings.

#include "AreaData.h"

// Sets default values
AAreaData::AAreaData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAreaData::Init(int _ID, int _x, int _y, int _width, int _height)
{
	MyStatus.AreaID = _ID;
	OwnerTop = _y;
	OwnerLeft = _x;

	// 区画サイズ
	MyStatus.AreaWidth = _width;
	MyStatus.RoomWidth = FMath::RandRange(5, MyStatus.AreaWidth - 5);
	MyStatus.AreaHeight = _height;
	MyStatus.RoomHeight = FMath::RandRange(5, MyStatus.AreaHeight - 5);
}

// 実際に部屋を生成
void AAreaData::CreateMap()
{
	FString path = "/Game/test.test_C"; // /Content 以下のパスが /Game 以下のパスに置き換わり、コンテントブラウザーで名前が test なら test.test_C を指定する。
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); // 上記で設定したパスに該当するクラスを取得

	// マップ生成
	// 生成位置
	FVector SpawnPos = FVector(MyStatus.Left * 100, MyStatus.Top * 100, 0);
	FVector SpawnScale = FVector(MyStatus.RoomWidth, MyStatus.RoomHeight, 0.2);
	// 足場の生成
	AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
	StageChip->SetActorLocation(SpawnPos);
	StageChip->SetActorScale3D(SpawnScale); 

	CreateRoad();
}

// 部屋の大きさ定義
void AAreaData::CreateRoom()
{
	// エリア位置から部屋の生成位置を定義していく
	MyStatus.Top = FMath::RandRange(OwnerTop,  (OwnerTop + MyStatus.AreaHeight) - MyStatus.RoomHeight);
	MyStatus.Bottom = MyStatus.Top + MyStatus.RoomHeight;
	MyStatus.Left = FMath::RandRange(OwnerLeft, (OwnerLeft + MyStatus.AreaWidth) - MyStatus.RoomWidth);
	MyStatus.Right = MyStatus.Left + MyStatus.RoomWidth;

	CreateMap();
}

// 通路を作っていく
void AAreaData::CreateRoad()
{
	FString path = "/Game/test.test_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	if (OwnerTop == 0 && OwnerLeft == 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Bottom;
		}
		else if (y < MyStatus.Bottom) {
			x = MyStatus.Right;
		}
		// マップ生成
		// 生成位置
		FVector SpawnPos = FVector(x * 100, y * 100, 0);
		FVector SpawnScale = FVector::ZeroVector;
		if (x < MyStatus.Right) {
			SpawnScale = FVector(2, (OwnerTop + MyStatus.AreaHeight) - y, 0.2);
		}
		else if (y < MyStatus.Bottom) {
			SpawnScale = FVector((OwnerLeft + MyStatus.AreaWidth) - x, 2, 0.2);
		}
		// 足場の生成
		AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
		StageChip->SetActorLocation(SpawnPos);
		StageChip->SetActorScale3D(SpawnScale);
	}
	if (OwnerTop != 0 && OwnerLeft == 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Top;
		}
		else if (y > MyStatus.Top) {
			x = MyStatus.Right;
		}

		// マップ生成
		// 生成位置
		FVector SpawnPos = FVector(x * 100, y * 100, 0);
		FVector SpawnScale = FVector::ZeroVector;
		if (x < MyStatus.Right) {
			SpawnScale = FVector(2, (MyStatus.Top - OwnerTop), 0.2);
		}
		else if (y < MyStatus.Bottom) {
			SpawnScale = FVector((OwnerLeft + MyStatus.AreaWidth) - x, 2, 0.2);
		}
		// 足場の生成
		AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
		FRotator ChipRotate = FRotator(0, 0, 180);
		StageChip->SetActorLocation(SpawnPos);
		StageChip->SetActorScale3D(SpawnScale);
		StageChip->SetActorRotation(ChipRotate);
	}
	if (OwnerLeft != 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Top;
		}
		else if (y > MyStatus.Top) {
			x = MyStatus.Right;
		}
	}
}

// Called when the game starts or when spawned
void AAreaData::BeginPlay()
{
	
}

// Called every frame
void AAreaData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

