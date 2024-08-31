#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pawn/TruckPawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "CoreMacros.h"

ATruckAIController::ATruckAIController()
{
	TruckPerceptionComponent = CreateDefaultSubobject <UAIPerceptionComponent>(TEXT("TruckPerceptionComponent"));
	TruckAIData = CreateDefaultSubobject<UTruckAIData>(TEXT("TruckAIData"));
}

void ATruckAIController::StartMovingWithoutEnemyAttack()
{
	GetBlackboardComponent()->SetValueAsEnum(FName("TruckAISubtreeSelect"),  static_cast<uint8>(FTruckAISubtree::MovingWithoutEnemyAttack));
}

void ATruckAIController::SetDestinationPoint(AActor* InDestination)
{
	GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), InDestination);
}

void ATruckAIController::SetTruckDestroyed(bool InDestroyed)
{
	GetBlackboardComponent()->SetValueAsBool(FName("IsTruckDestroyed"), InDestroyed);
	auto TruckPawn = GetPawn<ATruckPawn>();
	TruckPawn->SetTruckDestroyed(InDestroyed);
}

void ATruckAIController::ChangeAISubtree(FTruckAISubtree InTruckAISubtree)
{
	GetBlackboardComponent()->SetValueAsEnum(FName("TruckAISubtreeSelect"), static_cast<uint8>(InTruckAISubtree));
}

void ATruckAIController::AllTruckStartReassemblingAfterEnemyDestroySubTree()
{
	UTruckAIData* Data = Cast<UTruckAIData>(GetBlackboardComponent()->GetValueAsObject(FName("TruckAIData")));

	if (IS_VALID(Data) == false)
	{
		return;
	}


	auto AITruckControllers = Data->GetTruckAIControllers();

	for (int i = 0; i < AITruckControllers.Num(); i++)
	{
		if (AITruckControllers[i].Get() == nullptr)
		{
			continue;
		}

		AITruckControllers[i]->ChangeAISubtree(FTruckAISubtree::ReassemblingAfterEnemyDestroyTruckInColumn);
	}
}

void ATruckAIController::AllTruckStartMovingWithoutEnemyAttack()
{
	UTruckAIData* Data = Cast<UTruckAIData>(GetBlackboardComponent()->GetValueAsObject(FName("TruckAIData")));

	if (IS_VALID(Data) == false)
	{
		return;
	}

	auto AITruckControllers = Data->GetTruckAIControllers();

	for (int i = 0; i < AITruckControllers.Num(); i++)
	{
		if (AITruckControllers[i].Get() == nullptr)
		{
			continue;
		}

		AITruckControllers[i]->ChangeAISubtree(FTruckAISubtree::MovingWithoutEnemyAttack);
	}
}

void ATruckAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			
		}
	}
}

void ATruckAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	TruckPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATruckAIController::PerceptionUpdated);
	RunBehaviorTree(BehaviorTree);
	GetBlackboardComponent()->SetValueAsObject(FName("TruckAIData"), TruckAIData);
}