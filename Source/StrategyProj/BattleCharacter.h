// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterInterface.h"
#include "Components/StaticMeshComponent.h"
#include "BattleCharacter.generated.h"

// 戦闘を行うキャラクタークラス
UCLASS()
class STRATEGYPROJ_API ABattleCharacter : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// コンストラクタ
	ABattleCharacter();

protected:

	// キャラクターの装備状態
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	EEquipmentState MyState;

	// キャラクターのステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	FCharacterStatus MyStatus;

	// カメラの回転量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	// カメラの回転量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Debug用(のちに削除)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterStatus")
	bool IsDebug;

	// 装備
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void EquipActive(UStaticMeshComponent* _EquipMesh, UStaticMeshComponent* _TargetMesh);

	// キャラクターの移動
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
	void NextMove(FVector _MoveVec);

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	// カメラ移動
	void TurnAtRate(float Rate);
	// カメラ移動
	void LookUpAtRate(float Rate);

	// 初回時の処理
	virtual void BeginPlay() override;

public:

	// 俯瞰視点かどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	bool BottomView;

	// 移動したかどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
	bool Moving;

	// 更新処理
	virtual void Tick(float DeltaTime) override;

	// インプットのセットアップ
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SpringArmの取得
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Cameraの取得
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
