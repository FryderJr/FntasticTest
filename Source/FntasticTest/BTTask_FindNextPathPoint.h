// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class FNTASTICTEST_API UBTTask_FindNextPathPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_FindNextPathPoint();
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Path;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector NextPathPoint;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PathCovered;

	UPROPERTY(EditAnywhere, Category = Parameters)
	float StepLength = 10.0f;

	UPROPERTY(EditAnywhere, Category = Parameters)
	bool bReverse = false;

private:

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
