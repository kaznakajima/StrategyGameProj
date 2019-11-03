// Fill out your copyright notice in the Description page of Project Settings.

#include "MagicActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMagicActor::AMagicActor()
{

	// セットアップ
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	// Particleのセットアップ
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyParticle"));
	MyParticle->SetupAttachment(SceneComponent);
	MyMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyMovement"));

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMagicActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// 進行方向を返す
FVector AMagicActor::GetMoveDirection(FVector TargetLocation)
{
	FVector MoveDirection = TargetLocation - GetActorLocation();

	return MoveDirection;
}

// Called every frame
void AMagicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

