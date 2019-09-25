// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "StrategyProjCharacter.h"
#include "RoomData.generated.h"

// 部屋のステータス
USTRUCT(BlueprintType)
struct FRoomStatus
{
	GENERATED_USTRUCT_BODY()

	// エリアID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaID;
	// 上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Top;
	// 下
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Bottom;
	// 左
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Left;
	// 右
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Right;
	// 部屋の横軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomWidth;
	// 部屋の縦軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomHeight;
};

// ルームデータクラス
UCLASS()
class STRATEGYPROJ_API ARoomData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomData();

	// 初期化
	void Init(int _ID, int _x, int _y, int _width, int _height);

	// 部屋の大きさを定義
	void CreateRoom();
	// 実際に部屋を生成
	void InitializeRoom();
	// エリア間の通路を作っていく
	void CreateRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);
	// 部屋が孤立しないように調節
	void ConnectRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// 区画情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FRoomStatus MyStatus;

	// 親の上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerTop;
	// 親の左
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerLeft;

	// 部屋のアクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	ARoomActor* MyRoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
