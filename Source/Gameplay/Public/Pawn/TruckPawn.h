#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetComponent.h"
#include "Data/TruckAIData.h"
#include "TruckPawn.generated.h"

class UFloatingPawnMovement;
class UBoxComponent;
class UNavModifierComponent;

TrackPawnArray FindAllPawnTrucks(UObject* InWorldContext);

UCLASS()
class GAMEPLAY_API ATruckPawn : public APawn
{
	GENERATED_BODY()

public:
	ATruckPawn();

	UFUNCTION(BlueprintCallable, Category = "Truck pawn")
	void SetTruckDestroyed(bool InIsTruckDestroyed);

	UFUNCTION(BlueprintPure, Category = "Truck pawn")
	bool GetIsTruckDestroyed() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetPawnWidgetNumber(int InNumber);

	void InitWidgetComponent();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void BlockArea();

	UFUNCTION(BlueprintCallable, Category = "UI")
	UWidgetComponent* GetWidgetComponent();

	virtual void Tick(float DeltaTime) override;

	template<class T>
	int GetPawnNumberFromWidgetComponent()
	{
		return Cast<T>(GetWidgetComponent()->GetUserWidgetObject())->GetTruckNumber();
	}

protected:
	bool IsTruckDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNavModifierComponent* BlockingObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track pawn")
	UStaticMesh* TruckStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track pawn")
	UStaticMesh* DestroyedTruckStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track pawn")
	UMaterialInterface* DestroyedTruckMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track pawn")
	UMaterialInterface* TruckMaterial;
};