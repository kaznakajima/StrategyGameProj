// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomActor.h"

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
ARoomActor::ARoomActor()
{
	// ƒƒbƒVƒ…‚Ì’è‹`
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	TileMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.2f));
	// l•û‚Ì’Ê˜H‚ğq‚É‚µ‚Ä‚¢‚­
	// ã
	Aisle_T_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_T"));
	Aisle_T_Mesh->SetupAttachment(TileMesh);
	Aisle_T_Mesh->SetRelativeLocation(FVector(0.0f, -67.0f, 0.0f));
	Aisle_T_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// ‰º
	Aisle_B_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_B"));
	Aisle_B_Mesh->SetupAttachment(TileMesh);
	Aisle_B_Mesh->SetRelativeLocation(FVector(0.0f, 67.0f, 0.0f));
	Aisle_B_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// ¶
	Aisle_L_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_L"));
	Aisle_L_Mesh->SetupAttachment(TileMesh);
	Aisle_L_Mesh->SetRelativeLocation(FVector(-67.0f, 0.0f, 0.0f));
	Aisle_L_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));
	// ‰E
	Aisle_R_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aisle_R"));
	Aisle_R_Mesh->SetupAttachment(TileMesh);
	Aisle_R_Mesh->SetRelativeLocation(FVector(67.0f, 0.0f, 0.0f));
	Aisle_R_Mesh->SetRelativeScale3D(FVector(0.35f, 0.35f, 1.0f));

 	// Tick‚ğ“K—p
	PrimaryActorTick.bCanEverTick = true;
}

// •”‰®“¯m‚ğ‚Â‚È‚®
void ARoomActor::ConnectRoom(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// •”‰®“¯m‚ÌˆÊ’uŠÖŒW
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// ‰¡’Ê˜H
	if (DifferencePos.X < 0.0f) {
		// ‚Â‚È‚®‚©‚Ç‚¤‚©‚Ì—”
		int IsConnect = FMath::RandRange(0, 100);

		// ’Ê˜H‚ğì‚é
		if (IsConnect > 49) {
			_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);

			// Ú‘±‚µ‚½•”‰®‚ğƒŠƒXƒg‚ÉŠi”[
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}

	// c’Ê˜H
	if (DifferencePos.Y < 0.0f) {
		// ‚Â‚È‚®‚©‚Ç‚¤‚©‚Ì—”
		int IsConnect = FMath::RandRange(0, 100);

		// ’Ê˜H‚ğì‚é
		if (IsConnect > 49) {
			_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);

			// Ú‘±‚µ‚½•”‰®‚ğƒŠƒXƒg‚ÉŠi”[
			_MyRoom->ConnectRoomList.Add(_OpponentRoom);
			_OpponentRoom->ConnectRoomList.Add(_MyRoom);
		}
	}
}

// ŒÇ—§‚µ‚È‚¢‚æ‚¤‚É’²®
void ARoomActor::RemainderConnect(ARoomActor * _MyRoom, ARoomActor * _OpponentRoom)
{
	// “¯‚¶‚à‚Ì‚ÍÈ‚­
	if (_MyRoom->ConnectRoomList.Contains(_OpponentRoom)) return;

	// •”‰®“¯m‚ÌˆÊ’uŠÖŒW
	FVector DifferencePos = _MyRoom->GetActorLocation() - _OpponentRoom->GetActorLocation();

	// ‰¡’Ê˜H
	if (DifferencePos.X < 0.0f) {
		_MyRoom->Aisle_R_Mesh->SetHiddenInGame(false);
	}
	// c’Ê˜H
	if (DifferencePos.Y < 0.0f) {
		_MyRoom->Aisle_B_Mesh->SetHiddenInGame(false);
	}

	// •”‰®“¯m‚ğ‚Â‚È‚¢‚Å‚¢‚­
	_MyRoom->ConnectRoomList.Add(_OpponentRoom);
	_OpponentRoom->ConnectRoomList.Add(_MyRoom);
}

// •”‰®‚ª‚Â‚È‚ª‚Á‚Ä‚¢‚é‚©ƒ`ƒFƒbƒN
void ARoomActor::CheckConnectRoom()
{
	// •”‰®‚ª‚Â‚È‚ª‚Á‚Ä‚¢‚È‚¢‚Ì‚È‚çíœ
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

