// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UIHelpers.h"
#include "Core/ScreenManager.h"
#include "GameInstance/TruckSimulatorGameInstance.h"
#include "Kismet/GameplayStatics.h"

UScreen* UUIHelpers::CreateScreen(UObject* InWorldContext, TSubclassOf<UScreen> InScreenType)
{
	auto GameInstance = Cast<UTruckSimulatorGameInstance>(UGameplayStatics::GetGameInstance(InWorldContext));
	UScreenManager* ScreenManager = GameInstance->GetScreenManager();
	return ScreenManager->CreateScreen(InScreenType);
}

void UUIHelpers::CloseScreen(UObject* InWorldContext, UScreen* InScreen)
{
	auto GameInstance = Cast<UTruckSimulatorGameInstance>(UGameplayStatics::GetGameInstance(InWorldContext));
	UScreenManager* ScreenManager = GameInstance->GetScreenManager();
	ScreenManager->CloseScreen(InScreen);
}
