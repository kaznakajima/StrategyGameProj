// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleCharacter.h"
#include "LongAttackActor.generated.h"

UCLASS()
class STRATEGYPROJ_API ALongAttackActor : public AActor
{
	GENERATED_BODY()
	
public:	

	// SceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		class USceneComponent* SceneComponent;
	// ����p��Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* WeaponMesh;
	// ProjectileMovementComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* MyMovement;

	// Sets default values for this actor's properties
	ALongAttackActor();

	// �e�L�����N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		ABattleCharacter* MyCharacter;

	// �^�[�Q�b�g�A�N�^�[
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* TargetActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �i�s������Ԃ�
	UFUNCTION(BlueprintPure, BlueprintCallable)
		FVector GetMoveDirection(FVector TargetLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ParticleSystem�̎擾
	FORCEINLINE class UStaticMeshComponent* GetFollowCamera() const { return WeaponMesh; }
	// ProjectileMovemet�̎擾
	FORCEINLINE class UProjectileMovementComponent* GetCameraBoom() const { return MyMovement; }
};
