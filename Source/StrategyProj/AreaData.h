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
	// ���̉���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaWidth;
	// ���̏c��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaHeight;
	// ���̉���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomWidth;
	// ���̏c��
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

	// ���ۂɕ����𐶐�
	void CreateMap();
	// �����̑傫�����`
	void CreateRoom();
	// �G���A�Ԃ̒ʘH������Ă���
	void CreateRoad();

	// �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FAreaStatus MyStatus;

	// �e�̏�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerTop;
	// �e�̍�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int OwnerLeft;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
