// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleCharacter.h"
#include "PlayerControllPawn.generated.h"

UCLASS()
class STRATEGYPROJ_API APlayerControllPawn : public APawn
{
	GENERATED_BODY()

	// SceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneComponent;
	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	APlayerControllPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// キャラクターのリスト
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<ABattleCharacter*> CharacterList;
	// キャラクターリストのインデックス番号
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	int Index;

	// 現在アクティブ(選択中)なキャラクター
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	ABattleCharacter* ActiveCharacter;

	UFUNCTION(BlueprintCallable, Category = "Character")
		ABattleCharacter* GetNextCharacter();

	// 俯瞰視点かどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	bool IsView;

	// カメラの回転量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	
	// カメラの回転量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// カメラ移動
	void TurnAtRate(float Rate);
	// カメラ移動
	void LookUpAtRate(float Rate);

public:	
	// 更新処理
	virtual void Tick(float DeltaTime) override;

	// インプットのセットアップ
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SceneComponentの取得
	FORCEINLINE class USceneComponent* GetSceneComponent() const { return DefaultSceneComponent; }
	// SpringArmの取得
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Cameraの取得
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
