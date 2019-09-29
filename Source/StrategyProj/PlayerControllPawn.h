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

	// 俯瞰視点かどうか
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	bool IsView;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
