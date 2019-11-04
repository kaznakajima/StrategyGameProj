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
	// 武器用のMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* WeaponMesh;
	// ProjectileMovementComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* MyMovement;

	// Sets default values for this actor's properties
	ALongAttackActor();

	// 親キャラクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		ABattleCharacter* MyCharacter;

	// ターゲットアクター
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor")
		AActor* TargetActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 進行方向を返す
	UFUNCTION(BlueprintPure, BlueprintCallable)
		FVector GetMoveDirection(FVector TargetLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ParticleSystemの取得
	FORCEINLINE class UStaticMeshComponent* GetFollowCamera() const { return WeaponMesh; }
	// ProjectileMovemetの取得
	FORCEINLINE class UProjectileMovementComponent* GetCameraBoom() const { return MyMovement; }
};
