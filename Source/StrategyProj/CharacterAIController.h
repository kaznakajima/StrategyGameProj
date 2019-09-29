// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

UCLASS()
class STRATEGYPROJ_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

	// ˆÚ“®Š®—¹‚ðŒŸ’m
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
