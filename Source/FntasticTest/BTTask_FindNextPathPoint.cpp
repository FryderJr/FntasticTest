// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextPathPoint.h"
#include "Path.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindNextPathPoint::UBTTask_FindNextPathPoint()
{
    bNotifyTick = false;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = false;
    NodeName = "FindNextPathPoint";

    Path.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextPathPoint, Path), AActor::StaticClass());
    NextPathPoint.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextPathPoint, NextPathPoint));
    PathCovered.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextPathPoint, PathCovered));
}

void UBTTask_FindNextPathPoint::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    UBlackboardData* BBAsset = GetBlackboardAsset();
    if (ensure(BBAsset))
    {
        Path.ResolveSelectedKey(*BBAsset);
        NextPathPoint.ResolveSelectedKey(*BBAsset);
        PathCovered.ResolveSelectedKey(*BBAsset);
    }
}

#pragma optimize("", off)

EBTNodeResult::Type UBTTask_FindNextPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    APawn* AIPawn = nullptr;
    AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (AIPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    
    APath* MyPath = nullptr;
    MyPath = Cast<APath>(MyBlackboard->GetValueAsObject(Path.SelectedKeyName));

    if (MyPath == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    float MyCoveredPath = MyBlackboard->GetValueAsFloat(PathCovered.SelectedKeyName);
    float Alpha = 0;
    const float PathLength = MyPath->GetPathLength();

    if (PathLength <= 0)
    {
        return EBTNodeResult::Failed;
    }

    if (bReverse)
    {
        Alpha = (MyCoveredPath - StepLength) / PathLength;
    }
    else
    {
        Alpha = (MyCoveredPath + StepLength) / PathLength;
    }

    if (Alpha < 0)
    {
        return EBTNodeResult::Failed;
    }

    if (Alpha > 0.96)
    {
        return EBTNodeResult::Failed;
    }

    float MyDistance = FMath::Lerp(0.0f, MyPath->GetPathLength(), Alpha);

    MyBlackboard->SetValueAsFloat(PathCovered.SelectedKeyName, MyDistance);

    MyBlackboard->SetValueAsVector(NextPathPoint.SelectedKeyName, MyPath->GetLocationAtDistance(MyDistance));

	return EBTNodeResult::Succeeded;
}
#pragma optimize("", on)