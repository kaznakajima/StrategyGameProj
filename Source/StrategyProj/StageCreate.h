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

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Width;
	// �c��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int Height;
	// �ŏ��̋��T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int MinAreaSize;
	// �ő�̋��T�C�Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int MaxAreaSize;
	// �ŏ��̋��̐�
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

	// �X�e�[�W�̃X�e�[�^�X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FStageStatus MyStatus;

protected:
	TArray<AAreaData*> AreaList;

	// �X�e�[�W������Ă���
	UFUNCTION(BlueprintCallable)
	void CreateMap();
	// �G���A�𐶐�����
	void CreateArea();
	// �G���A�Ԃ̒ʘH������Ă���
	void CreateRoad();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
