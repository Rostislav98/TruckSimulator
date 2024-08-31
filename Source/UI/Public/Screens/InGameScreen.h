#pragma once

#include "CoreMinimal.h"
#include "Core/Screen.h"
#include "InGameScreen.generated.h"

class UButton;

UCLASS()
class UI_API UInGameScreen : public UScreen
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnButtonStarMovingPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonRestartMapPressed();

	UFUNCTION()
	void OnButtonDestroyRandomTruck();

	UFUNCTION()
	void OnButtonExitGamePressed();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonStartMoving;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonRestartMap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonExitGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ButtonDestroyRandomTruck;
};
