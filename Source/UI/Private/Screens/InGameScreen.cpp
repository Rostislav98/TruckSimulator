#include "Screens/InGameScreen.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/GameSimulationGameMode.h"

void UInGameScreen::NativeConstruct()
{
	ButtonStartMoving->OnClicked.AddUniqueDynamic(this, &UInGameScreen::OnButtonStarMovingPressed);
	ButtonRestartMap->OnClicked.AddUniqueDynamic(this, &UInGameScreen::OnButtonRestartMapPressed);
	ButtonExitGame->OnClicked.AddUniqueDynamic(this, &UInGameScreen::OnButtonExitGamePressed);
	ButtonDestroyRandomTruck->OnClicked.AddUniqueDynamic(this, &UInGameScreen::OnButtonDestroyRandomTruck);
}

void UInGameScreen::OnButtonStarMovingPressed()
{
	auto GameMode = UGameplayStatics::GetGameMode(GetWorld());
	auto SimulationGameMode = Cast<AGameSimulationGameMode>(GameMode);

	if (SimulationGameMode != nullptr)
	{
		ButtonStartMoving->SetIsEnabled(false);
		SimulationGameMode->StartMovingWithoutEnemyAttack();
	}
}

void UInGameScreen::OnButtonDestroyRandomTruck()
{
	auto GameMode = UGameplayStatics::GetGameMode(GetWorld());
	auto SimulationGameMode = Cast<AGameSimulationGameMode>(GameMode);

	if (SimulationGameMode == nullptr)
	{
		return;
	}

	SimulationGameMode->DestroyRandomTruck();

	if (SimulationGameMode->GetNumAliveTrucks() == 0)
	{
		ButtonDestroyRandomTruck->SetIsEnabled(false);
	}
}

void UInGameScreen::OnButtonExitGamePressed()
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference { EQuitPreference::Quit };
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, QuitPreference, true);
}
