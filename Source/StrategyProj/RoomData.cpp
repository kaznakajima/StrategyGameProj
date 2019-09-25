// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomData.h"

// Sets default values
ARoomData::ARoomData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// ������
void ARoomData::Init(int _ID, int _x, int _y, int _width, int _height)
{
	// �����̃X�e�[�^�X��`
	MyStatus.AreaID = _ID;
	OwnerTop = _y;
	OwnerLeft = _x;
	
	MyStatus.RoomWidth = _width - 2;
	MyStatus.RoomHeight = _height - 2;
}

// �����̏���`
void ARoomData::InitializeRoom()
{
	// �G���A�ʒu���畔���̐����ʒu���`���Ă���
	MyStatus.Top = OwnerTop;
	MyStatus.Bottom = MyStatus.Top + MyStatus.RoomHeight;
	MyStatus.Left = OwnerLeft;
	MyStatus.Right = MyStatus.Left + MyStatus.RoomWidth;

	CreateRoom();
}

// �����̐���
void ARoomData::CreateRoom()
{
	// �����p�̃A�N�^�[�̏���
	FString path = "/Game/MyRoomActor.MyRoomActor_C"; 
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	// �}�b�v����
	// �����ʒu
	FVector SpawnPos = FVector(MyStatus.Left, MyStatus.Top, 0);
	FVector SpawnScale = FVector(MyStatus.RoomWidth, MyStatus.RoomHeight, 0.2);
	// ����̐���
	AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
	StageChip->SetActorLocation(SpawnPos);
	StageChip->SetActorScale3D(SpawnScale);
	StageChip->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	MyRoom = Cast<ARoomActor>(StageChip);
}

// �ʘH�̐���
void ARoomData::CreateRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom)
{
	_MyRoom->ConnectRoom(_MyRoom, _OpponentRoom);
}

// �Ǘ����Ȃ��悤����
void ARoomData::ConnectRoad(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// �Ȃ��ł���
	if (_OpponentRoom->ConnectRoomList.Num() == 1) {
		_MyRoom->RemainderConnect(_MyRoom, _OpponentRoom);
	}
}

// �������Ȃ����Ă��邩�`�F�b�N
void ARoomData::CheckRoomConnect()
{
}

// Called when the game starts or when spawned
void ARoomData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

