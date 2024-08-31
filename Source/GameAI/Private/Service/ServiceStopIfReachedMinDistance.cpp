#include "Service/ServiceStopIfReachedMinDistance.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Logging/StructuredLog.h"

UServiceStopIfReachedMinDistance::UServiceStopIfReachedMinDistance()
{
	RestoreSpeedAfterExitFromService = false;
	StopDistance = 500;
}

void UServiceStopIfReachedMinDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr && MyBlackboard != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("NextConvoyTruck"));
		const double Distance = FVector::Dist(TargetActor->GetActorLocation(), AIController->GetPawn()->GetActorLocation());
		auto MovementComponent = AIController->GetPawn()->FindComponentByClass<UFloatingPawnMovement>();
		const int32 NodeInstanceIdx = OwnerComp.FindInstanceContainingNode(this);
		FBTStopIfReachedMinDistanceMemory* MyMemory = CastInstanceNodeMemory<FBTStopIfReachedMinDistanceMemory>(OwnerComp.GetNodeMemory(this, NodeInstanceIdx));

		if (Distance <= StopDistance )
		{
			if (MovementComponent->MaxSpeed != 0)
			{
				MyMemory->SpeedBeforeStopping = MovementComponent->MaxSpeed;
			}
			
			MovementComponent->MaxSpeed = 0;
		}
		
		if (Distance > StopDistance && MyMemory->SpeedBeforeStopping != -1)
		{
			MovementComponent->MaxSpeed = MyMemory->SpeedBeforeStopping;
		}
		
	}
}

void UServiceStopIfReachedMinDistance::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FBTStopIfReachedMinDistanceMemory>(NodeMemory, InitType);
}

void UServiceStopIfReachedMinDistance::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FBTStopIfReachedMinDistanceMemory>(NodeMemory, CleanupType);
}

void UServiceStopIfReachedMinDistance::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (RestoreSpeedAfterExitFromService == false)
	{
		return;
	}

	AAIController* AIController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

	if (AIController != nullptr && MyBlackboard != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("NextConvoyTruck"));
		const double Distance = FVector::Dist(TargetActor->GetActorLocation(), AIController->GetPawn()->GetActorLocation());
		auto MovementComponent = AIController->GetPawn()->FindComponentByClass<UFloatingPawnMovement>();
		const int32 NodeInstanceIdx = OwnerComp.FindInstanceContainingNode(this);
		FBTStopIfReachedMinDistanceMemory* MyMemory = CastInstanceNodeMemory<FBTStopIfReachedMinDistanceMemory>(OwnerComp.GetNodeMemory(this, NodeInstanceIdx));
		MovementComponent->MaxSpeed = MyMemory->SpeedBeforeStopping;
	}
}
