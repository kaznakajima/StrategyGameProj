// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RoomActor.generated.h"

// ルームアクタークラス
UCLASS()
class STRATEGYPROJ_API ARoomActor : public AActor
{
	GENERATED_BODY()

public:	
	// コンストラクタ
	ARoomActor();

	// 部屋そのもののメッシュ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	class UStaticMeshComponent* TileMesh;

	//------------------部屋の四方の通路------------------
	// 上
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_T_Mesh;
	// 下
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_B_Mesh;
	// 左
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_L_Mesh;
	// 右
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_R_Mesh;
	//------------------------------------------------------

	// つながっている部屋のリスト
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	TArray<ARoomActor*> ConnectRoomList;

	// 部屋用のエフェクト
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	AActor* RoomEffect;

	// 部屋同士をつなぐ
	UFUNCTION(BlueprintCallable, Category = "RoomFunc")
	void ConnectRoom(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// 孤立しないように調整
	void RemainderConnect(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// 部屋がつながっているかチェック
	bool CheckConnectRoom();

protected:
	// 部屋の状態を初期化
	UFUNCTION(BlueprintCallable, Category = "RoomAction")
	void RoomImitialize();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 部屋のメッシュの取得
	FORCEINLINE class UStaticMeshComponent* GetTileMesh() const { return TileMesh; }

	// ------------------部屋の四方の通路------------------
	// 上
	FORCEINLINE class UStaticMeshComponent* GetAisle_T_Mesh() const { return Aisle_T_Mesh; }
	// 下
	FORCEINLINE class UStaticMeshComponent* GetAisle_B_Mesh() const { return Aisle_B_Mesh; }
	// 左
	FORCEINLINE class UStaticMeshComponent* GetAisle_L_Mesh() const { return Aisle_L_Mesh; }
	// 右
	FORCEINLINE class UStaticMeshComponent* GetAisle_R_Mesh() const { return Aisle_B_Mesh; }
	//------------------------------------------------------

};
