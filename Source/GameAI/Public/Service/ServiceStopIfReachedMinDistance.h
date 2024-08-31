#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceStopIfReachedMinDistance.generated.h"

struct FBTStopIfReachedMinDistanceMemory
{
	double SpeedBeforeStopping = -1;
};


UCLASS()
class GAMEAI_API UServiceStopIfReachedMinDistance : public UBTService
{
	GENERATED_BODY()
	
public:
	UServiceStopIfReachedMinDistance();
	
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	uint16 GetInstanceMemorySize() const override { return sizeof(FBTStopIfReachedMinDistanceMemory); }

	void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;

	void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;

	void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	double StopDistance;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool RestoreSpeedAfterExitFromService;
};
