// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreate.h"
#include "Kismet/GameplayStatics.h"
#include "BattleCharacter.h"
#include "WeaponActor.h"
#include "CharacterAIController.h"

// コンストラクタ
AMapCreate::AMapCreate()
{
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
		// 部屋が削除されているなら処理を行わない
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

	// ユニットを配置していく
	UnitSpawn();

	// 装備品生成
	WeaponSpawn();
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
	FString NormalPath = "/Game/Character/MyBattleCharacter.MyBattleCharacter_C";
	TSubclassOf<class ABattleCharacter> NormalCharacter = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*NormalPath)).LoadSynchronous();
	FString CommanderPath = "/Game/Character/CommanderCharacter.CommanderCharacter_C";
	TSubclassOf<class ABattleCharacter> CommanderCharacter = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*CommanderPath)).LoadSynchronous();

	// 生成カウント数
	int Count = 1;
	// リストを初期化
	IndexList.Empty();
	while (Count < MyStatus.UnitCount + 1) {

		// ランダムで生成する
		int Index = FMath::RandRange(0, AreaList.Num() - 1);
		// 被らないようにチェック
		for (int _Index : IndexList) {
			if (_Index == Index) continue;
		}

		IndexList.Add(Index);

		// 味方と敵判別
		if (Count % 2 != 0) {
			// キャラクターの生成
			ABattleCharacter* Character = nullptr;
			// 指揮官
			if (Count == 1) {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(CommanderCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("EnemyCommander"));
			}
			// 兵士
			else {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(NormalCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("EnemyNormal"));
			}

			Character->SpawnDefaultController();
			FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
			Character->SetActorLocation(SpawnPos);
		}
		else {
			// キャラクターの生成
			ABattleCharacter* Character = nullptr;
			// 指揮官
			if (Count == 2) {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(CommanderCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("PlayerCommander"));
			}
			// 兵士
			else {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(NormalCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("PlayerNormal"));
			}

			Character->SpawnDefaultController();
			FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
			Character->SetActorLocation(SpawnPos);
		}

		Count++;
	}
}

// 装備品の生成
void AMapCreate::WeaponSpawn()
{
	// 生成カウント数
	int Count = 0;
	// リストを初期化
	IndexList.Empty();
	while (Count < 4) {

		// ランダムに生成
		int Index = FMath::RandRange(0, AreaList.Num() - 1);
		// 被らないようにチェック
		for (int _Index : IndexList) {
			if (_Index == Index) continue;
		}

		IndexList.Add(Index);

		// ランダムで装備品を配置
		int WeaponIndex = FMath::RandRange(0, WeaponPath.Num() - 1);
		TSubclassOf<class AWeaponActor> Weapon = TSoftClassPtr<AWeaponActor>(FSoftObjectPath(*WeaponPath[WeaponIndex])).LoadSynchronous();

		FVector SpawnPos = FVector::ZeroVector;

		// ランダムに生成していく
		// 生成位置の定義
		SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 100.0f);
		// 部屋の設置
		AWeaponActor* NewWeapon = GetWorld()->SpawnActor<AWeaponActor>(Weapon);
		NewWeapon->SetActorLocation(SpawnPos);

		Count++;
	}
}

// 初回処理
void AMapCreate::BeginPlay()
{
	// 武器のPathリスト
	WeaponPath.Add("/Game/Items/W_Sword.W_Sword_C");
	WeaponPath.Add("/Game/Items/W_TwoHandSword.W_TwoHandSword_C");
	WeaponPath.Add("/Game/Items/W_Shild.W_Shild_C");
	WeaponPath.Add("/Game/Items/W_Bow.W_Bow_C");

	CreateMap();
}

// 更新処理
void AMapCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

