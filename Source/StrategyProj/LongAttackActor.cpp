// Fill out your copyright notice in the Description page of Project Settings.

#include "LongAttackActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ALongAttackActor::ALongAttackActor()
{
	// セットアップ
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	// Particleのセットアップ
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponActor"));
	WeaponMesh->SetupAttachment(SceneComponent);
	MyMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyMovement"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALongAttackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// 進行方向を返す
FVector ALongAttackActor::GetMoveDirection(FVector TargetLocation)
{
	FVector MoveDirection = TargetLocation - GetActorLocation();

	return MoveDirection;
}

// Called every frame
void ALongAttackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

