// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// �Z�b�g�A�b�v
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(SceneComponent);
}

// �X�e�[�^�X�̏�����
void AWeaponActor::InitializeStatus(FName _RowName)
{
	// �f�[�^�̒��o
	auto record = DataTable->FindRow<FWeaponStatusData>(_RowName, FString());

	// �l�̐ݒ�
	MyStatus.HP= record->HP;
	MyStatus.SP = record->SP;
	MyStatus.STR = record->STR;
	MyStatus.DEF = record->DEF;
	MyStatus.AVO = record->AVO;
}
