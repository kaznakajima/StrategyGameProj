// Fill out your copyright notice in the Description page of Project Settings.

#include "StageCreate.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStageCreate::AStageCreate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// �S�̃}�b�v�𐶐�
void AStageCreate::CreateMap()
{

}

// �����𐶐�
void AStageCreate::CreateArea()
{
	FString path = "/Game/room.room_C"; 
	TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); 

	int SplitValueX= FMath::RandRange(1, 3);
	int SplitValueY = FMath::RandRange(1, 3);
	for (int num = 0; num < MyStatus.MinAreaNum; num++) {
		int x = 16 * SplitValueX, y = 16 * SplitValueY;

		// �ŏ��̃G���A
		if (AreaList.Num() == 0) {
			FVector SpawnPos = FVector(num, num, 0);
			AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
			NewArea->Init(num, num, num, x, y);
			NewArea->SetActorLocation(SpawnPos);
			NewArea->CreateRoom();
			AreaList.Add(NewArea);

			// �v���C���[�̏����ʒu���`
			AStrategyProjCharacter* PlayerCharacter = Cast<AStrategyProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (PlayerCharacter != nullptr) {
				SpawnPos = FVector(NewArea->MyStatus.Left * 100, NewArea->MyStatus.Top * 100, 120);
				PlayerCharacter->SetActorLocation(SpawnPos);
			}
		}
		// �ǉ��G���A
		else {
			if (AreaList[num - 1]->OwnerLeft + AreaList[num - 1]->MyStatus.AreaWidth > MyStatus.Width) {
				CreateRoad();
				return;
			}

			// �c�����ɃG���A�����
			if (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight < MyStatus.Height) {
				// ���T�C�Y�͈�O�̃G���A�Ɠ���ɂ���
				int width = AreaList[num - 1]->MyStatus.AreaWidth;
				// �c�T�C�Y�͎c���Ă���̈悩�烉���_��
				int height = MyStatus.Height - (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight);
				FVector SpawnPos = FVector(AreaList[num - 1]->OwnerLeft * 100, (MyStatus.Height - height) * 100, 0);
				AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
				NewArea->Init(num, AreaList[num - 1]->OwnerLeft, MyStatus.Height - height, width, height);
				NewArea->SetActorLocation(SpawnPos);
				NewArea->CreateRoom();
				AreaList.Add(NewArea);
			}
			// �������ɃG���A�����
			else if (AreaList[num - 1]->OwnerTop + AreaList[num - 1]->MyStatus.AreaHeight >= MyStatus.Height) {
				// ���T�C�Y�͎c���Ă���̈悩�烉���_��
				int width = AreaList[num - 1]->OwnerLeft + AreaList[num - 1]->MyStatus.AreaWidth;
				SplitValueX = FMath::RandRange(1, (MyStatus.Width - width) / 16);
				// �c�T�C�Y�͊��S�Ƀ����_��
				SplitValueY = FMath::RandRange(1, 3);
				x = 16 * SplitValueX, y = 16 * SplitValueY;
				FVector SpawnPos = FVector(width * 100, 0, 0);
				AAreaData* NewArea = GetWorld()->SpawnActor<AAreaData>(sc);
				NewArea->Init(num, width, 0, x, y);
				NewArea->SetActorLocation(SpawnPos);
				NewArea->CreateRoom();
				AreaList.Add(NewArea);
			}
		}
	}
}

// �G���A�Ԃ̒ʘH������Ă���
void AStageCreate::CreateRoad()
{
}

// Called when the game starts or when spawned
void AStageCreate::BeginPlay()
{
	CreateArea();
}

// Called every frame
void AStageCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

