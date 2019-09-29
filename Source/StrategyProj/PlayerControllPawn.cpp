// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllPawn.h"

// Sets default values
APlayerControllPawn::APlayerControllPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerControllPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerControllPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerControllPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

