// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RoomActor.generated.h"

// ���[���A�N�^�[�N���X
UCLASS()
class STRATEGYPROJ_API ARoomActor : public AActor
{
	GENERATED_BODY()

public:	
	// �R���X�g���N�^
	ARoomActor();

	// �������̂��̂̃��b�V��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	class UStaticMeshComponent* TileMesh;

	//------------------�����̎l���̒ʘH------------------
	// ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_T_Mesh;
	// ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_B_Mesh;
	// ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_L_Mesh;
	// �E
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
		class UStaticMeshComponent* Aisle_R_Mesh;
	//------------------------------------------------------

	// �Ȃ����Ă��镔���̃��X�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	TArray<ARoomActor*> ConnectRoomList;

	// �����p�̃G�t�F�N�g
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RoomParts")
	AActor* RoomEffect;

	// �������m���Ȃ�
	UFUNCTION(BlueprintCallable, Category = "RoomFunc")
	void ConnectRoom(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// �Ǘ����Ȃ��悤�ɒ���
	void RemainderConnect(ARoomActor* _MyRoom, ARoomActor* _OpponentRoom);

	// �������Ȃ����Ă��邩�`�F�b�N
	bool CheckConnectRoom();

protected:
	// �����̏�Ԃ�������
	UFUNCTION(BlueprintCallable, Category = "RoomAction")
	void RoomImitialize();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �����̃��b�V���̎擾
	FORCEINLINE class UStaticMeshComponent* GetTileMesh() const { return TileMesh; }

	// ------------------�����̎l���̒ʘH------------------
	// ��
	FORCEINLINE class UStaticMeshComponent* GetAisle_T_Mesh() const { return Aisle_T_Mesh; }
	// ��
	FORCEINLINE class UStaticMeshComponent* GetAisle_B_Mesh() const { return Aisle_B_Mesh; }
	// ��
	FORCEINLINE class UStaticMeshComponent* GetAisle_L_Mesh() const { return Aisle_L_Mesh; }
	// �E
	FORCEINLINE class UStaticMeshComponent* GetAisle_R_Mesh() const { return Aisle_B_Mesh; }
	//------------------------------------------------------

};
