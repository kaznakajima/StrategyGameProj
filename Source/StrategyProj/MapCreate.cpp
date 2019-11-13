// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreate.h"
#include "Kismet/GameplayStatics.h"
#include "BattleCharacter.h"
#include "WeaponActor.h"
#include "CharacterAIController.h"

// �R���X�g���N�^
AMapCreate::AMapCreate()
{
	PrimaryActorTick.bCanEverTick = true;
}

// �}�b�v�̐���
void AMapCreate::CreateMap()
{
	FString path = "/Game/StageParts/MyRoomData.MyRoomData_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();
	FVector SpawnPos = FVector::ZeroVector;
	// ���������
	for (int numY = 0; numY < MyStatus.RoomCount; numY++) {
		for (int numX = 0; numX < MyStatus.RoomCount; numX++) {
			// �����ʒu�̒�`
			 SpawnPos = FVector(numX * (MyStatus.AreaSize * 100), numY * (MyStatus.AreaSize * 100), 0);
			// �����̐ݒu
			ARoomData* NewRoom = GetWorld()->SpawnActor<ARoomData>(sc);
			NewRoom->Init(numY + numX, SpawnPos.X, SpawnPos.Y, MyStatus.AreaSize, MyStatus.AreaSize);
			NewRoom->SetActorLocation(SpawnPos);	// �ʒu����
			NewRoom->InitializeRoom();						// �����̏�񏉊���
			AreaList.Add(NewRoom);							// ���X�g�ɕۑ�
		}
	}

	// �������m���Ȃ��ł���
	for (int num = 0; num < MyStatus.RoomCount * MyStatus.RoomCount; num++) {
		// ���ƂȂ�
		if ((num + 1) % MyStatus.RoomCount != 0) AreaList[num]->CreateRoad(AreaList[num]->MyRoom, AreaList[num + 1]->MyRoom);
		// �c�ƂȂ�
		if (num < MyStatus.RoomCount * (MyStatus.RoomCount - 1)) {
			AreaList[num]->CreateRoad(AreaList[num]->MyRoom, AreaList[num + MyStatus.RoomCount]->MyRoom);
		}

		// �������Ȃ����Ă��Ȃ��Ȃ�폜
		if (AreaList[num]->MyRoom->CheckConnectRoom()) AreaList[num]->MyRoom = NULL;
	}

	// �������Ǘ����Ȃ��悤�ɒ���
	for (int num = 0; num < MyStatus.RoomCount *  MyStatus.RoomCount - 1; num++) {
		// �������폜����Ă���Ȃ珈�����s��Ȃ�
		if (AreaList[num]->MyRoom != nullptr) {
			if (AreaList[num + 1]->MyRoom != nullptr && (num + 1) % MyStatus.RoomCount != 0) AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + 1]->MyRoom);

			if (num < MyStatus.RoomCount * (MyStatus.RoomCount - 1) && AreaList[num + MyStatus.RoomCount]->MyRoom != nullptr) {
				AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + MyStatus.RoomCount]->MyRoom);
			}
		}
	}

	// �Ȃ����Ă��Ȃ��������폜
	for (ARoomData* room : AreaList) {
		if (room->MyRoom == nullptr) AreaList.Remove(room);
	}

	// ���j�b�g��z�u���Ă���
	UnitSpawn();

	// �����i����
	WeaponSpawn();
}

// �̈�̐���
void AMapCreate::CreateArea()
{

}

// �ʘH�𐶐�
void AMapCreate::CreateRoad()
{

}

// ���j�b�g�̐���
void AMapCreate::UnitSpawn()
{
	FString NormalPath = "/Game/Character/MyBattleCharacter.MyBattleCharacter_C";
	TSubclassOf<class ABattleCharacter> NormalCharacter = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*NormalPath)).LoadSynchronous();
	FString CommanderPath = "/Game/Character/CommanderCharacter.CommanderCharacter_C";
	TSubclassOf<class ABattleCharacter> CommanderCharacter = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*CommanderPath)).LoadSynchronous();

	// �����J�E���g��
	int Count = 1;
	// ���X�g��������
	IndexList.Empty();
	while (Count < MyStatus.UnitCount + 1) {

		// �����_���Ő�������
		int Index = FMath::RandRange(0, AreaList.Num() - 1);
		// ���Ȃ��悤�Ƀ`�F�b�N
		for (int _Index : IndexList) {
			if (_Index == Index) continue;
		}

		IndexList.Add(Index);

		// �����ƓG����
		if (Count % 2 != 0) {
			// �L�����N�^�[�̐���
			ABattleCharacter* Character = nullptr;
			// �w����
			if (Count == 1) {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(CommanderCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("EnemyCommander"));
			}
			// ���m
			else {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(NormalCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("EnemyNormal"));
			}

			Character->SpawnDefaultController();
			FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
			Character->SetActorLocation(SpawnPos);
		}
		else {
			// �L�����N�^�[�̐���
			ABattleCharacter* Character = nullptr;
			// �w����
			if (Count == 2) {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(CommanderCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("PlayerCommander"));
			}
			// ���m
			else {
				Character = GetWorld()->SpawnActor<ABattleCharacter>(NormalCharacter);
				if (Character == nullptr) return;
				Character->InitializeStatus(FName("PlayerNormal"));
			}

			Character->SpawnDefaultController();
			FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
			Character->SetActorLocation(SpawnPos);
		}

		Count++;
	}
}

// �����i�̐���
void AMapCreate::WeaponSpawn()
{
	// �����J�E���g��
	int Count = 0;
	// ���X�g��������
	IndexList.Empty();
	while (Count < 4) {

		// �����_���ɐ���
		int Index = FMath::RandRange(0, AreaList.Num() - 1);
		// ���Ȃ��悤�Ƀ`�F�b�N
		for (int _Index : IndexList) {
			if (_Index == Index) continue;
		}

		IndexList.Add(Index);

		// �����_���ő����i��z�u
		int WeaponIndex = FMath::RandRange(0, WeaponPath.Num() - 1);
		TSubclassOf<class AWeaponActor> Weapon = TSoftClassPtr<AWeaponActor>(FSoftObjectPath(*WeaponPath[WeaponIndex])).LoadSynchronous();

		FVector SpawnPos = FVector::ZeroVector;

		// �����_���ɐ������Ă���
		// �����ʒu�̒�`
		SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 100.0f);
		// �����̐ݒu
		AWeaponActor* NewWeapon = GetWorld()->SpawnActor<AWeaponActor>(Weapon);
		NewWeapon->SetActorLocation(SpawnPos);

		Count++;
	}
}

// ���񏈗�
void AMapCreate::BeginPlay()
{
	// �����Path���X�g
	WeaponPath.Add("/Game/Items/W_Sword.W_Sword_C");
	WeaponPath.Add("/Game/Items/W_TwoHandSword.W_TwoHandSword_C");
	WeaponPath.Add("/Game/Items/W_Shild.W_Shild_C");
	WeaponPath.Add("/Game/Items/W_Bow.W_Bow_C");

	CreateMap();
}

// �X�V����
void AMapCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

