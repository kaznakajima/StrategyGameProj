// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BattleCharacter.h"
#include "BattleStage.generated.h"

UCLASS()
class STRATEGYPROJ_API ABattleStage : public AActor
{
	GENERATED_BODY()
	
public:	
	// コンストラクタ
	ABattleStage();

	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	
	// SceneCapture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneCaptureComponent2D* P_CaptureCamera; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneCaptureComponent2D* E_CaptureCamera;

	// RootComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class USceneComponent* Root;

	// メインタイル
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* MainTile;

	// CaptureCameraで撮影
	UFUNCTION(Blueprintcallable, Category = "CameraAction")
		void Capture();

protected:
	// 初回処理
	virtual void BeginPlay() override;

public:	
	// 更新処理
	virtual void Tick(float DeltaTime) override;

	// SpringArmの取得
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Cameraの取得
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// RootComponentの取得
	FORCEINLINE class USceneComponent* GetRoot() const { return Root; }
	// メインタイルの取得
	FORCEINLINE class UStaticMeshComponent* GetMainTile() const { return MainTile; }
	// SceneCaptureの取得
	FORCEINLINE class USceneCaptureComponent2D* Get1PCaptureCamera() const { return P_CaptureCamera; }
	FORCEINLINE class USceneCaptureComponent2D* Get2PCaptureCamera() const { return E_CaptureCamera; }
};
