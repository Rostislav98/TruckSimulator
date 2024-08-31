#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceControlDistanceToTarget.generated.h"

UCLASS()
class GAMEAI_API UServiceControlDistanceToTarget : public UBTService
{
	GENERATED_BODY()
public:
	UServiceControlDistanceToTarget();
	
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	double StandartSpeedIntervalLowerValue;

	UPROPERTY(EditAnywhere, Category = "AI")
	double StandartSpeedIntervalUpperValue;

	UPROPERTY(EditAnywhere, Category = "AI")
	double SpeedCatchingUpTruck;

	UPROPERTY(EditAnywhere, Category = "AI")
	double SlowDrivingSpeed;

	UPROPERTY(EditAnywhere, Category = "AI")
	double StandartSpeed;

};
