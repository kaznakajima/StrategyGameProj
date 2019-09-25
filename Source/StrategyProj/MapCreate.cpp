// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCreate.h"
#include "Kismet/GameplayStatics.h"

// �R���X�g���N�^
AMapCreate::AMapCreate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// �}�b�v�̐���
void AMapCreate::CreateMap()
{
	FString path = "/Game/MyRoomData.MyRoomData_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	// ���������
	for (int numY = 0; numY < MyStatus.RoomCount; numY++) {
		for (int numX = 0; numX < MyStatus.RoomCount; numX++) {

			FVector SpawnPos = FVector(numX * (MyStatus.AreaSize * 100), numY * (MyStatus.AreaSize * 100), 0);
			ARoomData* NewRoom = GetWorld()->SpawnActor<ARoomData>(sc);
			NewRoom->Init(numY + numX, SpawnPos.X, SpawnPos.Y, MyStatus.AreaSize, MyStatus.AreaSize);
			NewRoom->SetActorLocation(SpawnPos);
			NewRoom->InitializeRoom();
			AreaList.Add(NewRoom);

			//// �v���C���[�̏����ʒu���`
			//AStrategyProjCharacter* PlayerCharacter = Cast<AStrategyProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			//if (PlayerCharacter != nullptr) {
			//	SpawnPos = FVector(NewRoom->MyStatus.Left * 100, NewRoom->MyStatus.Top * 100, 120);
			//	PlayerCharacter->SetActorLocation(SpawnPos);
			//}
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
		AreaList[num]->MyRoom->CheckConnectRoom();
	}

	// �������Ǘ����Ȃ��悤�ɒ���
	for (int num = 0; num < MyStatus.RoomCount *  MyStatus.RoomCount - 1; num++) {
		// �������폜����Ă���Ȃ烊�^�[��
		if (AreaList[num]->MyRoom == nullptr) return;
		
		if (AreaList[num + 1]->MyRoom != nullptr && (num + 1) % MyStatus.RoomCount != 0) AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + 1]->MyRoom);

		if (num < MyStatus.RoomCount * (MyStatus.RoomCount - 1) && AreaList[num + MyStatus.RoomCount]->MyRoom != nullptr) {
			AreaList[num]->ConnectRoad(AreaList[num]->MyRoom, AreaList[num + MyStatus.RoomCount]->MyRoom);
		}
	}
}

// �̈�̐���
void AMapCreate::CreateArea()
{

}

// �ʘH�𐶐�
void AMapCreate::CreateRoad()
{

}

// Called when the game starts or when spawned
void AMapCreate::BeginPlay()
{
	CreateMap();
}

// Called every frame
void AMapCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

