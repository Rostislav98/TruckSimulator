// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TruckSimulatorGameInstance.generated.h"

class UScreenManager;

UCLASS()
class GAMEPLAY_API UTruckSimulatorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTruckSimulatorGameInstance();

	UFUNCTION(BlueprintPure, Category = "UI")
	UScreenManager* GetScreenManager();

protected:
	UPROPERTY()
	UScreenManager* ScreenManager;
};
