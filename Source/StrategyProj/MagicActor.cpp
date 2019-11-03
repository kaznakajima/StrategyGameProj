// Fill out your copyright notice in the Description page of Project Settings.

#include "MagicActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMagicActor::AMagicActor()
{

	// �Z�b�g�A�b�v
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	// Particle�̃Z�b�g�A�b�v
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

// �i�s������Ԃ�
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

