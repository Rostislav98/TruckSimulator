#include "GameInstance/TruckSimulatorGameInstance.h"
#include "Core/ScreenManager.h"

UTruckSimulatorGameInstance::UTruckSimulatorGameInstance()
{
    ScreenManager = CreateDefaultSubobject<UScreenManager>("ScreenManager");
}

UScreenManager* UTruckSimulatorGameInstance::GetScreenManager()
{
    return ScreenManager;
}
