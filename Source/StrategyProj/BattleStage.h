// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BattleStage.generated.h"

UCLASS()
class STRATEGYPROJ_API ABattleStage : public AActor
{
	GENERATED_BODY()
	
public:	
	// �R���X�g���N�^
	ABattleStage();

	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	// RootComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class USceneComponent* Root;

	// ���C���^�C��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* MainTile;

protected:
	// ���񏈗�
	virtual void BeginPlay() override;

public:	
	// �X�V����
	virtual void Tick(float DeltaTime) override;

	// SpringArm�̎擾
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Camera�̎擾
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// RootComponent�̎擾
	FORCEINLINE class USceneComponent* GetRoot() const { return Root; }

	// ���C���^�C���̎擾
	FORCEINLINE class UStaticMeshComponent* GetMainTile() const { return MainTile; }
};
