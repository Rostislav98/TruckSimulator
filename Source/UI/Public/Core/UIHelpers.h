#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIHelpers.generated.h"

class UScreen;

UCLASS()
class UI_API UUIHelpers : public UObject
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "UI")
	static UScreen* CreateScreen(UObject* InWorldContext, TSubclassOf<UScreen> InScreenType);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	static void CloseScreen(UObject* InWorldContext, UScreen* InScreen);
};
