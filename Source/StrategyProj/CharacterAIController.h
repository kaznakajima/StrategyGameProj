// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

UCLASS()
class STRATEGYPROJ_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// AI‚ð“®‚©‚¹‚é
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AI_Move")
		void RunAI();

	// ˆÚ“®Š®—¹‚ðŒŸ’m
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
