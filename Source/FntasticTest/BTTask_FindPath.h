// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPath.generated.h"

/**
 * Finds nearest APath object and stores it in blackboardkey
 */
UCLASS()
class FNTASTICTEST_API UBTTask_FindPath : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_FindPath();

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Path;

private:

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
