#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "TruckAIController.generated.h"

class UAIPerceptionComponent;
class UTruckAIData;

UENUM(BlueprintType)
enum class FTruckAISubtree : uint8
{
	None = 0,
	MovingWithoutEnemyAttack,
	ReassemblingAfterEnemyDestroyTruckInColumn
};

UCLASS()
class GAMEAI_API ATruckAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATruckAIController();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void StartMovingWithoutEnemyAttack();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetDestinationPoint(AActor* InDestination);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetTruckDestroyed(bool InDestroyed);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ChangeAISubtree(FTruckAISubtree InTruckAISubtree);

	void AllTruckStartReassemblingAfterEnemyDestroySubTree();

	void AllTruckStartMovingWithoutEnemyAttack();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UAIPerceptionComponent* GetPerceptionComponent() override { return TruckPerceptionComponent; }

protected:
	void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI")
	UAIPerceptionComponent* TruckPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	UTruckAIData* TruckAIData;
};
