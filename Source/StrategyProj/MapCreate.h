// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomData.h"
#include "MapCreate.generated.h"

// マップのステータス
USTRUCT(BlueprintType)
struct FMapStatus
{
	GENERATED_USTRUCT_BODY()

	// 横軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Width;
	// 縦軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Height;
	// 配置するユニット数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int UnitCount;
	// 最小の区画サイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaSize;
	// 部屋の数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomCount;
};

// マップクリエイトクラス
UCLASS()
class STRATEGYPROJ_API AMapCreate : public AActor
{
	GENERATED_BODY()
	
public:	
	// コンストラクタ
	AMapCreate();

	// ステージのステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FMapStatus MyStatus;

protected:
	// 部屋のリスト
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room")
	TArray<ARoomData*> AreaList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room")
	int FirstLocation;

	// ステージを作っていく
	UFUNCTION(BlueprintCallable)
	void CreateMap();
	// エリアを生成する
	void CreateArea();
	// エリア間の通路を作っていく
	void CreateRoad();

	UFUNCTION(BlueprintCallable)
	// ユニットの生成
	void UnitSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
