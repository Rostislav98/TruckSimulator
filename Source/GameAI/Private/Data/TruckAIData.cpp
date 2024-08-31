#include "Data/TruckAIData.h"
#include "AIController/TruckAIController.h"

void UTruckAIData::SetTrackPawnArray(TArray<TWeakObjectPtr<ATruckPawn>> InTrackPawnArray)
{
	TruckArray = InTrackPawnArray;
}

TArray<TWeakObjectPtr<ATruckPawn>> UTruckAIData::GetTruckPawnArray() const
{
	return TruckArray;
}

TruckAIControllerArray UTruckAIData::GetTruckAIControllers() const
{
	return TruckAIControllers;
}

void UTruckAIData::SetTruckAIControllersPawnArray(TruckAIControllerArray TruckAIControllerArray)
{
	TruckAIControllers = TruckAIControllerArray;
}