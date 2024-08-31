#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController/TruckAIController.h"
#include "ChangeTruckSubTree.generated.h"

UCLASS()
class GAMEAI_API UChangeTruckSubTree: public UBTTaskNode
{
	GENERATED_BODY()
	
public:	
	UChangeTruckSubTree();

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category ="AI")
	FTruckAISubtree TruckAISubTreeToChange;
};
