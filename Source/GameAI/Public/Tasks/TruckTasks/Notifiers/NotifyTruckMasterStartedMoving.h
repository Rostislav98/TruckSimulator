#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NotifyTruckMasterStartedMoving.generated.h"

class ATruckAIController;

UCLASS()
class GAMEAI_API UNotifyTruckMasterStartedMoving : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void NotifyAllSlaverTrucks(ATruckAIController* InAIController);
};
