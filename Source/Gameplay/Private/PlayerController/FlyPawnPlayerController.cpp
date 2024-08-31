#include "PlayerController/FlyPawnPlayerController.h"
#include "Pawn/TruckPawn.h"
#include "Widgets/TruckNumberWidget.h"
#include "AIController/TruckAIController.h"

void AFlyPawnPlayerController::Num1Pressed()
{
	const int KEY_NUM = 1;
	SetDestroyTruckView(KEY_NUM);
}

void AFlyPawnPlayerController::Num2Pressed()
{
	const int KEY_NUM = 2;
	SetDestroyTruckView(KEY_NUM);
}

void AFlyPawnPlayerController::Num3Pressed()
{
	const int KEY_NUM = 3;
	SetDestroyTruckView(KEY_NUM);
}

void AFlyPawnPlayerController::Num4Pressed()
{
	const int KEY_NUM = 4;
	SetDestroyTruckView(KEY_NUM);
}

void AFlyPawnPlayerController::Num5Pressed()
{
	const int KEY_NUM = 5;
	SetDestroyTruckView(KEY_NUM);
}

void AFlyPawnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Num1Pressed", EInputEvent::IE_Pressed, this, &AFlyPawnPlayerController::Num1Pressed);
	InputComponent->BindAction("Num2Pressed", EInputEvent::IE_Pressed, this, &AFlyPawnPlayerController::Num2Pressed);
	InputComponent->BindAction("Num3Pressed", EInputEvent::IE_Pressed, this, &AFlyPawnPlayerController::Num3Pressed);
	InputComponent->BindAction("Num4Pressed", EInputEvent::IE_Pressed, this, &AFlyPawnPlayerController::Num4Pressed);
	InputComponent->BindAction("Num5Pressed", EInputEvent::IE_Pressed, this, &AFlyPawnPlayerController::Num5Pressed);
}

void AFlyPawnPlayerController::BeginPlay()
{
	PawnsArray = FindAllPawnTrucks(this);
}

void AFlyPawnPlayerController::SetDestroyTruckView(int InInputKey) const
{
	for (int i = 0; i < PawnsArray.Num(); i++)
	{
		if (PawnsArray[i].Get() == nullptr)
		{
			continue;
		}

		const int Num = PawnsArray[i].Get()->GetPawnNumberFromWidgetComponent<UTruckNumberWidget>();

		if (InInputKey == Num)
		{
			PawnsArray[i].Get()->GetController<ATruckAIController>()->SetTruckDestroyed(true);
			PawnsArray[i].Get()->GetController<ATruckAIController>()->AllTruckStartReassemblingAfterEnemyDestroySubTree();
			break;
		}
	}
}
