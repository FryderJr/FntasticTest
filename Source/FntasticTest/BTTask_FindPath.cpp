// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPath.h"
#include "Path.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPath::UBTTask_FindPath()
{
    bNotifyTick = false;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = false;
    NodeName = "FindPath";

    Path.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindPath, Path), AActor::StaticClass());
}

void UBTTask_FindPath::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    UBlackboardData* BBAsset = GetBlackboardAsset();
    if (ensure(BBAsset))
    {
        Path.ResolveSelectedKey(*BBAsset);
    }
}

EBTNodeResult::Type UBTTask_FindPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }
    float NearestDistance = 5000.0f;
    APath* NearestPath = nullptr;
    UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    TArray<AActor*> AllPaths;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APath::StaticClass(), AllPaths);
    if (AllPaths.Num() <= 0)
    {
        return EBTNodeResult::Failed;
    }
    for (int32 i = 0; i < AllPaths.Num(); i++)
    {
        if (!NearestPath)
        {
            NearestDistance = (AllPaths[i]->GetActorLocation() - AIPawn->GetActorLocation()).Size();
            NearestPath = Cast<APath>(AllPaths[i]);
        }
        if ((AllPaths[i]->GetActorLocation() - AIPawn->GetActorLocation()).Size() < NearestDistance)
        {
            NearestDistance = (AllPaths[i]->GetActorLocation() - AIPawn->GetActorLocation()).Size();
            NearestPath = Cast<APath>(AllPaths[i]);
        }
    }
    if (!NearestPath)
    {
        return EBTNodeResult::Failed;
    }
    MyBlackboard->SetValueAsObject(Path.SelectedKeyName, NearestPath);
	return EBTNodeResult::Succeeded;
}
