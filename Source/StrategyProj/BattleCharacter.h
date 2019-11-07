// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterInterface.h"
#include "WeaponInterface.h"
#include "Components/StaticMeshComponent.h"
#include "RoomActor.h"
#include "BattleCharacterData.h"
#include "BattleCharacter.generated.h"

// 動的マルチキャストデリゲート(イベントディスパッチャー)の宣言
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterMoveEvent, bool, IsCancel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterEquipEvent, EEquipmentState, IsCancel);

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

	// SceneCapture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneCaptureComponent2D* CaptureCamera;

	// EventDispatcher(移動終了イベント)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FCharacterMoveEvent MoveEndEvent;
	// EventDispatcher(装備取得イベント)
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event")
		FCharacterEquipEvent EquipEvent;

	// ステータスの初期化
	UFUNCTION(BlueprintCallable, Category = "Character")
		void InitializeStatus(FName _RowName);

	// ダメージイベント
	void OnDamage_Implementation(float MagicPower, AActor* actor, float defence) override;

	// コリジョン有効化
	void OnUseCollision_Implementation(class UPrimitiveComponent* Col) override;

	// コリジョン無効化
	void OnUnUseCollision_Implementation(class UPrimitiveComponent* Col_1, class UPrimitiveComponent* Col_2) override;

	// 自身の部屋での立ち位置
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FVector MyLocation;

	// 対戦する敵キャラクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		ABattleCharacter* BattleEnemy;

	// 自分がプレイヤーのチームかどうか
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		bool GetIsPlayerTeam();

	// 現在の装備状態を返す
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		EEquipmentState GetEquipState();
	// 現在の装備状態を返す
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Character")
		EBattleState GetBattleState();

	// バトル中かどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		bool IsBattle;

protected:

	// データテーブル
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EditData")
		UDataTable* DataTable;

	// キャラクターのステータス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		FCharacterStatus MyStatus;
	// 現在のHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float CurrentHP;
	// 現在のSP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		float CurrentSP;

	// 自身のいる部屋
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterStatus")
		ARoomActor* CurrentRoom;

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
		void EquipActive(UStaticMeshComponent* _EquipMesh, UStaticMeshComponent* _TargetMesh, FTransform _EquipTransform);
	// 装備状態の設定
	UFUNCTION(BlueprintCallable, Category = "Equip")
		void EquipSetting(EEquipmentState _State, FWeaponStatus _Status);

	// 戦闘ステートの設定
	UFUNCTION(BlueprintCallable, Category = "Equip")
		void BattleSetting(EBattleState _State);

	// キャラクターの移動(ターゲット指定)
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
		void NextMove(AActor* _TargetActor, float _Range);

	// 元の地点に戻る
	UFUNCTION(BlueprintCallable, Category = "CharacterAction")
		void ResetMove(FVector _OffsetLocation, float _Range);
	
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

	// 移動キャンセルイベント
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void MoveCancel();

	// 戦闘準備イベント
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void BattlePrepare();

	// 戦闘アクション開始イベント(開始の瞬間)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void ActionMove();

	// 戦闘イベント(実際のアクション)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void ActionEvent();

	// 戦闘アクション終了イベント
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "CharacterAction")
		void ActionEnd();

	// 更新処理
		virtual void Tick(float DeltaTime) override;

	// インプットのセットアップ
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// SpringArmの取得
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Cameraの取得
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// SceneCaptureの取得
	FORCEINLINE class USceneCaptureComponent2D* GetCaptureCamera() const { return CaptureCamera; }
};
