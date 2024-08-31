#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UpdateTruckConvoyInformation.generated.h"

class ATruckPawn;

UCLASS()
class GAMEAI_API UUpdateTruckConvoyInformation : public UBTTaskNode
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void FindAllTrucks(UBlackboardComponent* InBlackboardComponent);

	void FindMasterTruckPawn(UBlackboardComponent* InBlackboardComponent, TArray<TWeakObjectPtr<ATruckPawn>> InTrackPawnArray);

};
