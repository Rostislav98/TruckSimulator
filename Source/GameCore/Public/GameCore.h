#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class GAMECORE_API FGameCoreModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
};
