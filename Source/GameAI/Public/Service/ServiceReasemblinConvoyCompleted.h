#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceReasemblinConvoyCompleted.generated.h"

UCLASS()
class GAMEAI_API UServiceReasemblinConvoyCompleted : public UBTService
{
	GENERATED_BODY()

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
