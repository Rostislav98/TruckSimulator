#include "GameMode/GameSimulationGameMode.h"
#include "Pawn/TruckPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/GamePlayerStart.h"
#include "Actors/TaskCompletedTriggerBox.h"
#include "Logging/StructuredLog.h"
#include "AIController/TruckAIController.h"

void AGameSimulationGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
    FindTruckSpawnPoints();
    SpawnTucks();
	FindTaskCompletedTriggerBox();
	IsSimulationStarted = false;
}

void AGameSimulationGameMode::SpawnTucks()
{
	for (int i = 0; i < PlayersStarts.Num(); i++)
	{
		if (PlayersStarts[i]->GetPlayerStartStatus() == GamePlayerStartStatus::WaitingTruckSpawn)
		{
			SpawnTruck(PlayersStarts[i]);
			PlayersStarts[i]->SetPlayerStartStatus(GamePlayerStartStatus::TruckSpawned);
		}
	}
}

void AGameSimulationGameMode::BeginPlay()
{
	SetupPawnWidgetNaming();
}

void AGameSimulationGameMode::SetupPawnWidgetNaming()
{
	int Index = 0;
	for (auto Truck : Trucks)
	{
		if (Truck.Get())
		{
			Index++;
			Truck->InitWidgetComponent();
			Truck->SetPawnWidgetNumber(Index);
		}
	}
}

void AGameSimulationGameMode::SpawnTruck(AGamePlayerStart* InPlayerStart)
{
	if (TruckToSpawnClass.Get() == nullptr)
	{
		UE_LOGFMT(LogGameMode, Error, "AGameSimulationGameMode::SpawnTruck: TruckToSpawnClass is nullptr");
		return;
	}

	FActorSpawnParameters SpawnParams;
	auto SpawnLocation = InPlayerStart->GetActorLocation();
	auto Truck = GetWorld()->SpawnActor<ATruckPawn>(TruckToSpawnClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	Trucks.Add(MakeWeakObjectPtr<ATruckPawn>(Truck));
}

void AGameSimulationGameMode::FindTruckSpawnPoints()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGamePlayerStart::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		PlayersStarts.Add(Cast<AGamePlayerStart>(FoundActors[i]));
	}
}

void AGameSimulationGameMode::FindTaskCompletedTriggerBox()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaskCompletedTriggerBox::StaticClass(), FoundActors);

	if (FoundActors.Num() < 2 && FoundActors.Num() != 0)
	{
		TaskCompletedTriggerBox = Cast<ATaskCompletedTriggerBox>(*FoundActors.begin());
	}
	else
	{
		UE_LOGFMT(LogGameMode, Error, "AGameSimulationGameMode::FindTaskCompletedTriggerBox: you have incorrect num of trigger box on level");
	}
}

AActor* AGameSimulationGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	Super::FindPlayerStart_Implementation(Player, TEXT(""));

	for (int i = 0; i < PlayersStarts.Num(); i++)
	{
		if (PlayersStarts[i]->GetPlayerStartStatus() == GamePlayerStartStatus::WaitingPlayerSpawn)
		{
			PlayersStarts[i]->SetPlayerStartStatus(GamePlayerStartStatus::PlayerSpawned);
			return PlayersStarts[i];
		}
	}
	
	return nullptr;
}

void AGameSimulationGameMode::StartMovingWithoutEnemyAttack()
{
	if (IsSimulationStarted == true)
	{
		UE_LOGFMT(LogGameMode, Warning, "AGameSimulationGameMode::StartGameSimulation(): game simulation has already started");
		return;
	}

	for (int i = 0; i < Trucks.Num(); i++)
	{
		if (Trucks[i].Get())
		{
			auto TruckAIController = Cast<ATruckAIController>(Trucks[i].Get()->GetController());
			
			if (TaskCompletedTriggerBox.Get())
			{
				
				TruckAIController->SetDestinationPoint(Cast<AActor>(TaskCompletedTriggerBox));
			}

			TruckAIController->StartMovingWithoutEnemyAttack();
		}
	}

	IsSimulationStarted = true;
}

void AGameSimulationGameMode::DestroyRandomTruck()
{	
	do
	{
		const int Index = FMath::RandRange(0, Trucks.Num() - 1);

		if (Trucks[Index].Get())
		{
			auto TruckAIController = Cast<ATruckAIController>(Trucks[Index].Get()->GetController());
			TruckAIController->SetTruckDestroyed(true);
			Trucks[Index]->SetTruckDestroyed(true);
			Trucks.RemoveAt(Index);
			break;
		}

		Trucks.RemoveAt(Index);
	}
	while (Trucks.Num() > 0);
}

int AGameSimulationGameMode::GetNumAliveTrucks()
{
	return Trucks.Num();
}