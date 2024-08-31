#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NotifyTruckSlaversCanStartMoving.generated.h"

class ATruckAIController;

UCLASS()
class GAMEAI_API UNotifyTruckSlaversCanStartMoving : public UBTTaskNode
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void NotifyAllSlaverTrucks(ATruckAIController* InAIController);
	
};
