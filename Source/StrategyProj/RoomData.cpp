// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomData.h"

// �R���X�g���N�^
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
	
	// �����̑傫���̒�`
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

	// �����̐���
	CreateRoom();
}

// �����̐���
void ARoomData::CreateRoom()
{
	// �����p�̃A�N�^�[�̏���
	FString path = "/Game/StageParts/MyRoomActor.MyRoomActor_C"; 
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
	// �����A�N�^�[�̊i�[
	MyRoom = Cast<ARoomActor>(StageChip);
}

// �ʘH�̐���
void ARoomData::CreateRoad(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom)
{
	// �ʘH������Ă���(�����_��)
	_MyRoom->ConnectRoom(_MyRoom, _OpponentRoom);
}

// �������Ǘ����Ȃ��悤����
void ARoomData::ConnectRoad(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// �ڑ������Ȃ���������Ȃ��ł���
	if (_MyRoom->ConnectRoomList.Num() == 1 && _OpponentRoom->ConnectRoomList.Num() > 0 ||
		_MyRoom->ConnectRoomList.Num() == 2 && _OpponentRoom->ConnectRoomList.Num() == 1) {
		_MyRoom->RemainderConnect(_MyRoom, _OpponentRoom);
	}
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

