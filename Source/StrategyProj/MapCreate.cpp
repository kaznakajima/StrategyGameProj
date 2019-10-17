// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreate.h"
#include "Kismet/GameplayStatics.h"
#include "BattleCharacter.h"
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

	for (int num = 0; num < MyStatus.UnitCount;num++) UnitSpawn(num);
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
void AMapCreate::UnitSpawn(int _UnitNum)
{
	FString PlayerPath = "/Game/Character/MyBattleCharacter.MyBattleCharacter_C";
	TSubclassOf<class ABattleCharacter> PlayerCharacter = TSoftClassPtr<ABattleCharacter>(FSoftObjectPath(*PlayerPath)).LoadSynchronous();

	int Index = FMath::RandRange(0, AreaList.Num() - 1);
	ABattleCharacter* Character = GetWorld()->SpawnActor<ABattleCharacter>(PlayerCharacter);
	if (Character == nullptr) return;

	Character->SpawnDefaultController();
	FVector SpawnPos = FVector(AreaList[Index]->GetActorLocation().X, AreaList[Index]->GetActorLocation().Y, 150.0f);
	Character->SetActorLocation(SpawnPos);

	// �����ƓG����
	if (_UnitNum / 2 < 1) {
		// �G�̂�AI���N��
		ACharacterAIController* Controller = Cast<ACharacterAIController>(Character->GetController());
		Controller->RunAI();
		Character->InitializeStatus(FName("EnemyNormal"));
	}
	else {
		Character->InitializeStatus(FName("PlayerNormal"));
	}
}

// ���񏈗�
void AMapCreate::BeginPlay()
{
	CreateMap();
}

// �X�V����
void AMapCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

