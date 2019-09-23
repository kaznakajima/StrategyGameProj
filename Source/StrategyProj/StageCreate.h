// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaData.h"
#include "StageCreate.generated.h"

USTRUCT(BlueprintType)
struct FStageStatus
{
	GENERATED_USTRUCT_BODY()

	// 横軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Width;
	// 縦軸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Height;
	// 最小の区画サイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int MinAreaSize;
	// 最大の区画サイズ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int MaxAreaSize;
	// 最小の区画の数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int MinAreaNum;
};

UCLASS()
class STRATEGYPROJ_API AStageCreate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageCreate();

	// ステージのステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FStageStatus MyStatus;

protected:
	TArray<AAreaData*> AreaList;

	// ステージを作っていく
	UFUNCTION(BlueprintCallable)
	void CreateMap();
	// エリアを生成する
	void CreateArea();
	// エリア間の通路を作っていく
	void CreateRoad();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
