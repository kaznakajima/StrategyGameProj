// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StrategyProjCharacter.h"
#include "AreaData.generated.h"

USTRUCT(BlueprintType)
struct FAreaStatus
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
	// 区画の横軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaWidth;
	// 区画の縦軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaHeight;
	// 区画の横軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomWidth;
	// 区画の縦軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomHeight;
};

UCLASS()
class STRATEGYPROJ_API AAreaData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaData();

	void Init(int _ID, int _x, int _y, int _width, int _height);

	// 実際に部屋を生成
	void CreateMap();
	// 部屋の大きさを定義
	void CreateRoom();
	// エリア間の通路を作っていく
	void CreateRoad();

	// 区画情報
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FAreaStatus MyStatus;

	// 親の上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerTop;
	// 親の左
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerLeft;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
