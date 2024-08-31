#include "Core/ScreenManager.h"
#include "Core/Screen.h"

UScreen* UScreenManager::CreateScreen(const TSubclassOf<UScreen>& InScreen)
{
	auto Widget = CreateWidget<UScreen>(GetWorld(), InScreen.Get());
	Widget->AddToViewport();
	ScreenArray.Add(Widget);
	return Widget;
}

void UScreenManager::CloseScreen(UScreen* InScreen)
{
	ScreenArray.Remove(InScreen);
	InScreen->RemoveFromParent();
}
