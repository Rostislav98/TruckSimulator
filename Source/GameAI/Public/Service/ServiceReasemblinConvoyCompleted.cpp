#include "ServiceReasemblinConvoyCompleted.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Data/TruckAIData.h"

void UServiceReasemblinConvoyCompleted::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ATruckAIController* AIController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr && MyBlackboard != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("NextConvoyTruck"));
		auto MovementComponent = AIController->GetPawn()->FindComponentByClass<UFloatingPawnMovement>();
		UTruckAIData* Data = Cast<UTruckAIData>(AIController->GetBlackboardComponent()->GetValueAsObject(FName("TruckAIData")));
		auto TruckAIControllers = Data->GetTruckAIControllers();

		for (int i = 0; i < TruckAIControllers.Num(); i++)
		{
			if (TruckAIControllers[i]->GetBlackboardComponent()->GetValueAsBool("IsTruckDestroyed"))
			{
				continue;
			}

			if (TruckAIControllers[i]->GetBlackboardComponent()->GetValueAsBool("IsTruckReasembled") == false)
			{
				return;
			}
		}

		// Reset values in FTruckAISubtree::ReassemblingAfterEnemyDestroyTruckInColumn subtree
		for (int i = 0; i < TruckAIControllers.Num(); i++)
		{
			TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool("IsTruckReasembled", false);
			TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool("IsConvoyDataUpdated", false);
			TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool("IsMasterStartedMoving", false);
			TruckAIControllers[i]->GetBlackboardComponent()->SetValueAsBool("IsCanSlaveStartMove", false);
		}

		AIController->AllTruckStartMovingWithoutEnemyAttack();
	}
}
