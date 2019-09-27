// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomActor.h"

// �R���X�g���N�^
ARoomActor::ARoomActor()
{
	// ���b�V���̒�`
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	TileMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.2f));
	// �l���̒ʘH���q�ɂ��Ă���
	// ��
	Aisle_T_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_T"));
	Aisle_T_Mesh->SetupAttachment(TileMesh);
	Aisle_T_Mesh->SetRelativeLocation(FVector(0.0f, -67.0f, 0.0f));
	Aisle_T_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// ��
	Aisle_B_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_B"));
	Aisle_B_Mesh->SetupAttachment(TileMesh);
	Aisle_B_Mesh->SetRelativeLocation(FVector(0.0f, 67.0f, 0.0f));
	Aisle_B_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// ��
	Aisle_L_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_L"));
	Aisle_L_Mesh->SetupAttachment(TileMesh);
	Aisle_L_Mesh->SetRelativeLocation(FVector(-67.0f, 0.0f, 0.0f));
	Aisle_L_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// �E
	Aisle_R_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_R"));
	Aisle_R_Mesh->SetupAttachment(TileMesh);
	Aisle_R_Mesh->SetRelativeLocation(FVector(67.0f, 0.0f, 0.0f));
	Aisle_R_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));

	// ParticleSystem�̃Z�b�g�A�b�v
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("P_Smoke"));
	ParticleSystem->SetupAttachment(TileMesh);

 	// Tick��K�p
	PrimaryActorTick.bCanEverTick = true;
}

// �������m���Ȃ�
void ARoomActor::ConnectRoom(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// �������m�̈ʒu�֌W
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// ���ʘH
	if (DifferencePos.X < 0.0f) {
		// �Ȃ����ǂ����̗���
		int IsConnect = FMath::RandRange(0, 100);

		// �ʘH�����
		if (IsConnect > 49) {
			_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);

			// �ڑ��������������X�g�Ɋi�[
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}

	// �c�ʘH
	if (DifferencePos.Y < 0.0f) {
		// �Ȃ����ǂ����̗���
		int IsConnect = FMath::RandRange(0, 100);

		// �ʘH�����
		if (IsConnect > 49) {
			_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);

			// �ڑ��������������X�g�Ɋi�[
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}
}

// �Ǘ����Ȃ��悤�ɒ���
void ARoomActor::RemainderConnect(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// �������̂͏Ȃ�
	if (_MyRoom->ConnectRoomList.Contains(_OpponentRoom)) return;

	// �������m�̈ʒu�֌W
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// ���ʘH
	if (DifferencePos.X < 0.0f) {
		_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);
	}
	// �c�ʘH
	if (DifferencePos.Y < 0.0f) {
		_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);
	}

	// �������m���Ȃ��ł���
	_MyRoom->ConnectRoomList.Add(_OpponentRoom);
	_OpponentRoom->ConnectRoomList.Add(_MyRoom);
}

// �������Ȃ����Ă��邩�`�F�b�N
void ARoomActor::CheckConnectRoom()
{
	// �������Ȃ����Ă��Ȃ��̂Ȃ�폜
	if (ConnectRoomList.Num() == 0) {
		Destroy();
		EndPlay(EEndPlayReason::Type::Destroyed);
	}
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
}

