#include "Tasks/TruckTasks/Notifiers/NotifyTruckMasterStartedMoving.h"
#include "Pawn/TruckPawn.h"
#include "Data/TruckAIData.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UNotifyTruckMasterStartedMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		Result = EBTNodeResult::Succeeded;
		NotifyAllSlaverTrucks(Cast<ATruckAIController>(MyController));
	}

	return Result;
}

void UNotifyTruckMasterStartedMoving::NotifyAllSlaverTrucks(ATruckAIController* InAIController)
{
	UTruckAIData* Data = Cast<UTruckAIData>(InAIController->GetBlackboardComponent()->GetValueAsObject("TruckAIData"));
	auto TruckAIControllers = Data->GetTruckAIControllers();

	for (int i = 0; i < TruckAIControllers.Num(); i++)
	{
		if (TruckAIControllers[i].Get() == nullptr)
		{
			continue;
		}
		
		bool IsMaterTruck = TruckAIControllers[i]->GetBlackboardComponent()->GetValueAsBool("IsMaster");
		
		if (IsMaterTruck == false)
		{
			TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool("IsMasterStartedMoving", true);
		}
	}
}
