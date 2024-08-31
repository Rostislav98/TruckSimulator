#include "Tasks/TruckTasks/FindNewMasterTruck.h"
#include "Pawn/TruckPawn.h"
#include "Data/TruckAIData.h"
#include "AIController/TruckAIController.h"
#include "Widgets/TruckNumberWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/WeakObjectPtrTemplates.h"

EBTNodeResult::Type UFindNewMasterTruck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATruckAIController*  MyController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		UTruckAIData* Data = Cast<UTruckAIData>(MyController->GetBlackboardComponent()->GetValueAsObject("TruckAIData"));
		auto TruckAIControllers = Data->GetTruckAIControllers();
		TruckAIControllers.Remove(MyController); // Remove self controller
		const int CurrentPawnNumber = MyController->GetPawn<ATruckPawn>()->GetPawnNumberFromWidgetComponent<UTruckNumberWidget>();
		TruckAIControllers.Sort([](auto A, auto B)
		{
			if (A.Get() == nullptr || B.Get() == nullptr)
			{
				return false;
			}

			const int Num1 = A->GetPawn<ATruckPawn>()->GetPawnNumberFromWidgetComponent<UTruckNumberWidget>();
			const int Num2 = B->GetPawn<ATruckPawn>()->GetPawnNumberFromWidgetComponent<UTruckNumberWidget>();

			if (Num1 < Num2)
			{
				return true;
			}
			else
			{
				return false;
			}
		});

		for (int i = 0; i < TruckAIControllers.Num(); i++)
		{	
			bool IsDestroyed = TruckAIControllers[i]->GetBlackboardComponent()->GetValueAsBool("IsTruckDestroyed");

			if (IsDestroyed == false)
			{
				MyController->GetBlackboardComponent()->SetValueAsBool(FName("IsMaster"), false);
				TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool(FName("IsMaster"), true);
				Result = EBTNodeResult::Succeeded;
				break;
			}
		}
	}

	return Result;
}
