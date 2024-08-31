#include "Tasks/TruckTasks/ChangeTruckSubTree.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UChangeTruckSubTree::UChangeTruckSubTree()
{
	TruckAISubTreeToChange = FTruckAISubtree::None;
}

EBTNodeResult::Type UChangeTruckSubTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATruckAIController* const MyController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		MyController->ChangeAISubtree(TruckAISubTreeToChange);
		Result = EBTNodeResult::Succeeded;
	}

	return Result;
}
