// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RoomActor.generated.h"

UCLASS()
class STRATEGYPROJ_API ARoomActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
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

	// 部屋同士をつなぐ
	UFUNCTION(BlueprintCallable, Category = "RoomFunc")
	void ConnectRoom(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// 他の部屋につながっているかチェック
	void CheckConnect();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetTileMesh() const { return TileMesh; }

	FORCEINLINE class UStaticMeshComponent* GetAisle_T_Mesh() const { return Aisle_T_Mesh; }
	FORCEINLINE class UStaticMeshComponent* GetAisle_B_Mesh() const { return Aisle_B_Mesh; }
	FORCEINLINE class UStaticMeshComponent* GetAisle_L_Mesh() const { return Aisle_L_Mesh; }
	FORCEINLINE class UStaticMeshComponent* GetAisle_R_Mesh() const { return Aisle_B_Mesh; }

};
