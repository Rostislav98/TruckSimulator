#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlyPawnPlayerController.generated.h"

class ATruckPawn;

UCLASS()
class GAMEPLAY_API AFlyPawnPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	void Num1Pressed();

	void Num2Pressed();

	void Num3Pressed();

	void Num4Pressed();

	void Num5Pressed();
	
protected:
	void SetupInputComponent() override;

	void BeginPlay() override;

	void SetDestroyTruckView(int InInputKey) const;

	TArray<TWeakObjectPtr<ATruckPawn>> PawnsArray;
};
