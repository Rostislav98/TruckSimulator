#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TruckAIData.generated.h"

class ATruckPawn;
class ATruckAIController;

using TrackPawnArray = TArray<TWeakObjectPtr<ATruckPawn>>;
using TruckAIControllerArray = TArray<TWeakObjectPtr<ATruckAIController>>;

UCLASS(Blueprintable, BlueprintType)
class GAMEAI_API UTruckAIData : public UObject
{
	GENERATED_BODY()
	
public:
	void SetTrackPawnArray(TArray<TWeakObjectPtr<ATruckPawn>> InTrackPawnArray);
	
	TArray<TWeakObjectPtr<ATruckPawn>> GetTruckPawnArray() const;

	TruckAIControllerArray GetTruckAIControllers() const;

	void SetTruckAIControllersPawnArray(TruckAIControllerArray TruckAIControllerArray);
	
protected:
	TrackPawnArray TruckArray;

	TruckAIControllerArray TruckAIControllers;
};
