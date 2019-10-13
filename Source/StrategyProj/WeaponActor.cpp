// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// セットアップ
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(SceneComponent);
}

// ステータスの初期化
void AWeaponActor::InitializeStatus(FName _RowName)
{
	// データの抽出
	auto record = DataTable->FindRow<FWeaponStatusData>(_RowName, FString());

	// 値の設定
	MyStatus.HP= record->HP;
	MyStatus.SP = record->SP;
	MyStatus.STR = record->STR;
	MyStatus.DEF = record->DEF;
	MyStatus.AVO = record->AVO;
}
