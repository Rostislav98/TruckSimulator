#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskSetValueIsTruckReasembled.generated.h"


UCLASS()
class GAMEAI_API UTaskSetValueIsTruckReasembled : public UBTTaskNode
{
	GENERATED_BODY()
public:	
	UTaskSetValueIsTruckReasembled();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	

	UPROPERTY(EditAnywhere, Category = "AI Data")
	bool IsTruckReasembled;
};
