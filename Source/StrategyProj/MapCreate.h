// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomData.h"
#include "MapCreate.generated.h"

// �}�b�v�̃X�e�[�^�X
USTRUCT(BlueprintType)
struct FMapStatus
{
	GENERATED_USTRUCT_BODY()

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Width;
	// �c��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Height;
	// �z�u���郆�j�b�g��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int UnitCount;
	// �ŏ��̋��T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int AreaSize;
	// �����̐�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int RoomCount;
};

// �}�b�v�N���G�C�g�N���X
UCLASS()
class STRATEGYPROJ_API AMapCreate : public AActor
{
	GENERATED_BODY()
	
public:	
	// �R���X�g���N�^
	AMapCreate();

	// �X�e�[�W�̃X�e�[�^�X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FMapStatus MyStatus;

protected:
	// �����̃��X�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room")
	TArray<ARoomData*> AreaList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Room")
	int FirstLocation;

	// �X�e�[�W������Ă���
	UFUNCTION(BlueprintCallable)
	void CreateMap();
	// �G���A�𐶐�����
	void CreateArea();
	// �G���A�Ԃ̒ʘH������Ă���
	void CreateRoad();

	UFUNCTION(BlueprintCallable)
	// ���j�b�g�̐���
	void UnitSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
