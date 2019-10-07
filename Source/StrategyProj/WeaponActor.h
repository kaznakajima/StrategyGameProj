// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponInterface.h"
#include "WeaponActor.generated.h"

UCLASS()
class STRATEGYPROJ_API AWeaponActor : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	AWeaponActor();

	// SceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		class USceneComponent* SceneComponent;
	// �s��p��Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* WeaponMesh;

	// ����̃p�����[�^
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		FWeaponStatus MyStatus;
};
