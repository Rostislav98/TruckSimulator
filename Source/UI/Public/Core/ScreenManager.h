#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScreenManager.generated.h"

class UScreen;

UCLASS(BlueprintType)
class UI_API UScreenManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	UScreen* CreateScreen(const TSubclassOf<UScreen>& InScreen);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CloseScreen(UScreen* InScreen);

protected:
	UPROPERTY()
	TArray<UScreen*> ScreenArray;
};
