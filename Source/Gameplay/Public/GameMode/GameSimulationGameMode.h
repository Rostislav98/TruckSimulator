#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameSimulationGameMode.generated.h"

class ATruckPawn;
class AGamePlayerStart;
class ATaskCompletedTriggerBox;

UCLASS()
class GAMEPLAY_API AGameSimulationGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartMovingWithoutEnemyAttack();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void DestroyRandomTruck();

	UFUNCTION(BlueprintPure, Category = "GameMode")
	int GetNumAliveTrucks();

protected:
	void SpawnTruck(AGamePlayerStart* InPlayerStart);

	void FindTruckSpawnPoints();

	void FindTaskCompletedTriggerBox();

	void SpawnTucks();

	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ATruckPawn> TruckToSpawnClass;

	UPROPERTY(Transient)
	TArray<AGamePlayerStart*> PlayersStarts;

	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<ATruckPawn>> Trucks;

	TWeakObjectPtr<ATaskCompletedTriggerBox> TaskCompletedTriggerBox;

	bool IsSimulationStarted;

private:
	void SetupPawnWidgetNaming();
};
