#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <Engine/EngineTypes.h>

class UCOVEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};