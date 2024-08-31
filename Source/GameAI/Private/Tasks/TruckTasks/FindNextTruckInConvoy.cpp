#include "Tasks/TruckTasks/FindNextTruckInConvoy.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawn/TruckPawn.h"
#include "Data/TruckAIData.h"
#include "Actors/TaskCompletedTriggerBox.h"
#include "Logging/StructuredLog.h"
#include "Components/WidgetComponent.h"
#include "Widgets/TruckNumberWidget.h"

EBTNodeResult::Type UFindNextTruckInConvoy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATruckAIController* const MyController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		Result = EBTNodeResult::Succeeded;
		UTruckAIData* Data = Cast<UTruckAIData>(MyController->GetBlackboardComponent()->GetValueAsObject("TruckAIData"));
		auto TruckAIControllers = Data->GetTruckAIControllers();
		auto TruckPawns = Data->GetTruckPawnArray();
		const FVector TargetLocationActor = MyController->GetPawn()->GetTransform().GetLocation();
		TruckPawns.Remove(MyController->GetPawn<ATruckPawn>());
		const int CurrentNumber = Cast<UTruckNumberWidget>(MyController->GetPawn<ATruckPawn>()->GetWidgetComponent()->GetUserWidgetObject())->GetTruckNumber();
		ATruckPawn* TargetActor = nullptr;
		int MinDiff = std::numeric_limits<int>::max();

		for (int i = 0; i < TruckPawns.Num(); i++)
		{
			if (TruckPawns[i].Get())
			{

				if(TruckPawns[i]->GetIsTruckDestroyed())
				{
					 continue;
				}

				const int Number = Cast<UTruckNumberWidget>(TruckPawns[i]->GetWidgetComponent()->GetUserWidgetObject())->GetTruckNumber();

				if (Number > CurrentNumber)
				{
					break;
				}

				int Diff = FMath::Abs(Number - CurrentNumber);
				
				if (Diff < MinDiff)
				{
					MinDiff = Diff;
					TargetActor = TruckPawns[i].Get();
				}
			}
		}

		if (TargetActor != nullptr)
		{
			MyController->GetBlackboardComponent()->SetValueAsObject("NextConvoyTruck", TargetActor);
		}
	}

	return Result;
}

