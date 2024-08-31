#include "Service/ServiceControlDistanceToTarget.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

UServiceControlDistanceToTarget::UServiceControlDistanceToTarget()
{
	bTickIntervals = true;
	StandartSpeedIntervalLowerValue = 200;
	StandartSpeedIntervalUpperValue = 500;
	SpeedCatchingUpTruck = 700;
	SlowDrivingSpeed = 200;
	StandartSpeed = 400;
}

void UServiceControlDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr && MyBlackboard != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("NextConvoyTruck"));
		const double Distance = FVector::Dist(TargetActor->GetActorLocation(), AIController->GetPawn()->GetActorLocation());
		auto MovementComponent = AIController->GetPawn()->FindComponentByClass<UFloatingPawnMovement>();

		if (MovementComponent->MaxSpeed == 0)
		{
			return;
		}

		if (Distance < StandartSpeedIntervalLowerValue)
		{
			 MovementComponent->MaxSpeed = SlowDrivingSpeed;
			 return;
		}

		if (Distance > StandartSpeedIntervalUpperValue)
		{
			MovementComponent->MaxSpeed = SpeedCatchingUpTruck;
			return;
		}

		MovementComponent->MaxSpeed = StandartSpeed;
	}
}