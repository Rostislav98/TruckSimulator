#include "Tasks/TruckTasks/SetValue/TaskSetValueIsTruckReasembled.h"
#include "Pawn/TruckPawn.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


UTaskSetValueIsTruckReasembled::UTaskSetValueIsTruckReasembled()
{
	IsTruckReasembled = false;
}

EBTNodeResult::Type UTaskSetValueIsTruckReasembled::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		Result = EBTNodeResult::Succeeded;
		MyController->GetBlackboardComponent()->SetValueAsBool("IsTruckReasembled", IsTruckReasembled);
	}

	return  Result;
}