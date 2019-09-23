// Fill out your copyright notice in the Description page of Project Settings.

#include "AreaData.h"

// Sets default values
AAreaData::AAreaData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAreaData::Init(int _ID, int _x, int _y, int _width, int _height)
{
	MyStatus.AreaID = _ID;
	OwnerTop = _y;
	OwnerLeft = _x;

	// ���T�C�Y
	MyStatus.AreaWidth = _width;
	MyStatus.RoomWidth = FMath::RandRange(5, MyStatus.AreaWidth - 5);
	MyStatus.AreaHeight = _height;
	MyStatus.RoomHeight = FMath::RandRange(5, MyStatus.AreaHeight - 5);
}

// ���ۂɕ����𐶐�
void AAreaData::CreateMap()
{
	FString path = "/Game/test.test_C"; // /Content �ȉ��̃p�X�� /Game �ȉ��̃p�X�ɒu�������A�R���e���g�u���E�U�[�Ŗ��O�� test �Ȃ� test.test_C ���w�肷��B
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); // ��L�Őݒ肵���p�X�ɊY������N���X���擾

	// �}�b�v����
	// �����ʒu
	FVector SpawnPos = FVector(MyStatus.Left * 100, MyStatus.Top * 100, 0);
	FVector SpawnScale = FVector(MyStatus.RoomWidth, MyStatus.RoomHeight, 0.2);
	// ����̐���
	AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
	StageChip->SetActorLocation(SpawnPos);
	StageChip->SetActorScale3D(SpawnScale); 

	CreateRoad();
}

// �����̑傫����`
void AAreaData::CreateRoom()
{
	// �G���A�ʒu���畔���̐����ʒu���`���Ă���
	MyStatus.Top = FMath::RandRange(OwnerTop,  (OwnerTop + MyStatus.AreaHeight) - MyStatus.RoomHeight);
	MyStatus.Bottom = MyStatus.Top + MyStatus.RoomHeight;
	MyStatus.Left = FMath::RandRange(OwnerLeft, (OwnerLeft + MyStatus.AreaWidth) - MyStatus.RoomWidth);
	MyStatus.Right = MyStatus.Left + MyStatus.RoomWidth;

	CreateMap();
}

// �ʘH������Ă���
void AAreaData::CreateRoad()
{
	FString path = "/Game/test.test_C";
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();

	if (OwnerTop == 0 && OwnerLeft == 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Bottom;
		}
		else if (y < MyStatus.Bottom) {
			x = MyStatus.Right;
		}
		// �}�b�v����
		// �����ʒu
		FVector SpawnPos = FVector(x * 100, y * 100, 0);
		FVector SpawnScale = FVector::ZeroVector;
		if (x < MyStatus.Right) {
			SpawnScale = FVector(2, (OwnerTop + MyStatus.AreaHeight) - y, 0.2);
		}
		else if (y < MyStatus.Bottom) {
			SpawnScale = FVector((OwnerLeft + MyStatus.AreaWidth) - x, 2, 0.2);
		}
		// ����̐���
		AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
		StageChip->SetActorLocation(SpawnPos);
		StageChip->SetActorScale3D(SpawnScale);
	}
	if (OwnerTop != 0 && OwnerLeft == 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Top;
		}
		else if (y > MyStatus.Top) {
			x = MyStatus.Right;
		}

		// �}�b�v����
		// �����ʒu
		FVector SpawnPos = FVector(x * 100, y * 100, 0);
		FVector SpawnScale = FVector::ZeroVector;
		if (x < MyStatus.Right) {
			SpawnScale = FVector(2, (MyStatus.Top - OwnerTop), 0.2);
		}
		else if (y < MyStatus.Bottom) {
			SpawnScale = FVector((OwnerLeft + MyStatus.AreaWidth) - x, 2, 0.2);
		}
		// ����̐���
		AActor* StageChip = GetWorld()->SpawnActor<AActor>(sc);
		FRotator ChipRotate = FRotator(0, 0, 180);
		StageChip->SetActorLocation(SpawnPos);
		StageChip->SetActorScale3D(SpawnScale);
		StageChip->SetActorRotation(ChipRotate);
	}
	if (OwnerLeft != 0) {
		int x = FMath::RandRange(MyStatus.Left, MyStatus.Right), y = FMath::RandRange(MyStatus.Top, MyStatus.Bottom);
		if (x < MyStatus.Right) {
			y = MyStatus.Top;
		}
		else if (y > MyStatus.Top) {
			x = MyStatus.Right;
		}
	}
}

// Called when the game starts or when spawned
void AAreaData::BeginPlay()
{
	
}

// Called every frame
void AAreaData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

