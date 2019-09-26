// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameControlPawn.generated.h"

// ゲーム進行用ポーン
UCLASS()
class STRATEGYPROJ_API AGameControlPawn : public APawn
{
	GENERATED_BODY()

	// StaticMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;
	// SpringArm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	AGameControlPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// StaticMeshを返す
	FORCEINLINE class UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }
	// SpringArmを返す
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return CameraBoom; }
	// FollowCameraを返す
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
