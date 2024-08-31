#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TruckNumberWidget.generated.h"

class UTextBlock;

UCLASS()
class UI_API UTruckNumberWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetTruckNumberText(FText InText);

	UFUNCTION(BlueprintPure, Category = "UI")
	int GetTruckNumber() const;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlockTruckNumber;
};
