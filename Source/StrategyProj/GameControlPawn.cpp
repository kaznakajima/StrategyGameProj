// Fill out your copyright notice in the Description page of Project Settings.

#include "GameControlPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGameControlPawn::AGameControlPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// StaticMesh�̃Z�b�g�A�b�v
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// SpringArm�̃Z�b�g�A�b�v
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(StaticMesh);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Camera�̃Z�b�g�A�b�v
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); 
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AGameControlPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameControlPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameControlPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}

