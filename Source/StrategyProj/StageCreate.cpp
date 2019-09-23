// Fill out your copyright notice in the Description page of Project Settings.

#include "StageCreate.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStageCreate::AStageCreate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// 全体マップを生成
void AStageCreate::CreateMap()
{

}

// 部屋を生成
void AStageCreate::CreateArea()
{
	FString path = "/Game/room.room_C"; 
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); 

	int SplitValueX= FMath::RandRange(1, 3);
	int SplitValueY = FMath::RandRange(1, 3);
	for (int num = 0; num < MyStatus.MinAreaNum; num++) {
		int x = 16 * SplitValueX, y = 16 * SplitValueY;

		// 最初のエリア
		if (AreaList.Num() == 0) {
			FVector SpawnPos = FVector(num, num, 0);
			AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
			NewArea->Init(num, num, num, x, y);
			NewArea->SetActorLocation(SpawnPos);
			NewArea->CreateRoom();
			AreaList.Add(NewArea);

			// プレイヤーの初期位置を定義
			AStrategyProjCharacter* PlayerCharacter = Cast<AStrategyProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (PlayerCharacter != nullptr) {
				SpawnPos = FVector(NewArea->MyStatus.Left * 100, NewArea->MyStatus.Top * 100, 120);
				PlayerCharacter->SetActorLocation(SpawnPos);
			}
		}
		// 追加エリア
		else {
			if (AreaList[num - 1]->OwnerLeft + AreaList[num - 1]->MyStatus.AreaWidth > MyStatus.Width) {
				CreateRoad();
				return;
			}

			// 縦方向にエリアを作る
			if (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight < MyStatus.Height) {
				// 横サイズは一つ前のエリアと同一にする
				int width = AreaList[num - 1]->MyStatus.AreaWidth;
				// 縦サイズは残っている領域からランダム
				int height = MyStatus.Height - (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight);
				FVector SpawnPos = FVector(AreaList[num - 1]->OwnerLeft * 100, (MyStatus.Height - height) * 100, 0);
				AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
				NewArea->Init(num, AreaList[num - 1]->OwnerLeft, MyStatus.Height - height, width, height);
				NewArea->SetActorLocation(SpawnPos);
				NewArea->CreateRoom();
				AreaList.Add(NewArea);
			}
			// 横方向にエリアを作る
			else if (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight >= MyStatus.Height) {
				// 横サイズは残っている領域からランダム
				int width = AreaList[num - 1]->OwnerLeft + AreaList[num - 1]->MyStatus.AreaWidth;
				SplitValueX = FMath::RandRange(1, (MyStatus.Width - width) / 16);
				// 縦サイズは完全にランダム
				SplitValueY = FMath::RandRange(1, 3);
				x = 16 * SplitValueX, y = 16 * SplitValueY;
				FVector SpawnPos = FVector(width * 100, 0, 0);
				AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
				NewArea->Init(num, width, 0, x, y);
				NewArea->SetActorLocation(SpawnPos);
				NewArea->CreateRoom();
				AreaList.Add(NewArea);
			}
		}
	}
}

// エリア間の通路を作っていく
void AStageCreate::CreateRoad()
{
}

// Called when the game starts or when spawned
void AStageCreate::BeginPlay()
{
	CreateArea();
}

// Called every frame
void AStageCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

