#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "GamePlayerStart.generated.h"

UENUM(BlueprintType)
enum class GamePlayerStartStatus : uint8
{
	None,
	WaitingPlayerSpawn,
	PlayerSpawned,
	WaitingTruckSpawn,
	TruckSpawned
};

UCLASS()
class GAMEPLAY_API AGamePlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	AGamePlayerStart(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Gameplay")
	GamePlayerStartStatus GetPlayerStartStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetPlayerStartStatus(GamePlayerStartStatus InPlayerStartStatus);

protected:
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	GamePlayerStartStatus PlayerStartStatus;
};
