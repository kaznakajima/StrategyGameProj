// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "StrategyProjCharacter.h"
#include "RoomData.generated.h"

// �����̃X�e�[�^�X
USTRUCT(BlueprintType)
struct FRoomStatus
{
	GENERATED_USTRUCT_BODY()

	// �G���AID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaID;
	// ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Top;
	// ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Bottom;
	// ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Left;
	// �E
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Right;
	// �����̉���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomWidth;
	// �����̏c��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomHeight;
};

// ���[���f�[�^�N���X
UCLASS()
class STRATEGYPROJ_API ARoomData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomData();

	// ������
	void Init(int _ID, int _x, int _y, int _width, int _height);

	// �����̑傫�����`
	void CreateRoom();
	// ���ۂɕ����𐶐�
	void InitializeRoom();
	// �G���A�Ԃ̒ʘH������Ă���
	void CreateRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);
	// �������Ǘ����Ȃ��悤�ɒ���
	void ConnectRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FRoomStatus MyStatus;

	// �e�̏�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerTop;
	// �e�̍�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerLeft;

	// �����̃A�N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room")
	ARoomActor* MyRoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
