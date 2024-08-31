#include "Tasks/TruckTasks/UpdateTruckConvoyInformation.h"
#include "AIController/TruckAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/TruckPawn.h"
#include "Data/TruckAIData.h"
#include "Logging/StructuredLog.h"
#include "Components/WidgetComponent.h"
#include "Widgets/TruckNumberWidget.h"

EBTNodeResult::Type UUpdateTruckConvoyInformation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATruckAIController* const MyController = Cast<ATruckAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (MyController && MyController->GetPawn())
	{
		Result = EBTNodeResult::Succeeded;
		FindAllTrucks(MyController->GetBlackboardComponent());
	}

	return Result;
}

void UUpdateTruckConvoyInformation::FindAllTrucks(UBlackboardComponent* InBlackboardComponent)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATruckPawn::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		TrackPawnArray Array;
		TruckAIControllerArray AIControllerArray;

		for (int i = 0; i < FoundActors.Num(); i++)
		{
			Array.Add(Cast<ATruckPawn>(FoundActors[i]));
			AIControllerArray.Add(Cast<ATruckPawn>(FoundActors[i])->GetController<ATruckAIController>());
		}

		FindMasterTruckPawn(InBlackboardComponent, Array);
		UTruckAIData* Data = Cast<UTruckAIData>(InBlackboardComponent->GetValueAsObject(FName("TruckAIData")));
		Data->SetTrackPawnArray(Array);
		Data->SetTruckAIControllersPawnArray(AIControllerArray);
		InBlackboardComponent->SetValueAsObject(FName("TruckAIData"), Data);
		InBlackboardComponent->SetValueAsBool(FName("IsConvoyDataUpdated"), true);
	}
	else
	{
		UE_LOGFMT(LogTemp, Warning, "ATruck actors is  not founded on map!");
	}
}

void UUpdateTruckConvoyInformation::FindMasterTruckPawn(UBlackboardComponent* InBlackboardComponent, TArray<TWeakObjectPtr<ATruckPawn>> InTrackPawnArray)
{
	bool FoundMasterPawn = false;

	for (int i = 0; i < InTrackPawnArray.Num(); i++)
	{
		if (InTrackPawnArray[i].Get())
		{
			auto WidgetComponent = InTrackPawnArray[i]->GetWidgetComponent();
			auto Widget = Cast<UTruckNumberWidget>(WidgetComponent->GetUserWidgetObject());
			int TruckNumber = Widget->GetTruckNumber();

			if (TruckNumber == 1)
			{
				FoundMasterPawn = true;
				auto AIController = InTrackPawnArray[i]->GetController<ATruckAIController>();
				AIController->GetBlackboardComponent()->SetValueAsBool(FName("IsMaster"), FoundMasterPawn);
			}

		}
	}

	if (FoundMasterPawn)
	{
		UE_LOGFMT(LogTemp, Warning, "ATruck doesn`t have master pawn!");
	}
}
