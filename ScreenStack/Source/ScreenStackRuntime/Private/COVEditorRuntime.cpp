#include "COVEditorRuntime.h"

#include "Engine.h"
#include <Engine/AssetManager.h>

#if WITH_EDITOR

#endif

#include "ScreenStack.h"
#include "Misc/UObjectToken.h"

void UCOVEditorRuntime::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void UCOVEditorRuntime::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#define LOCTEXT_NAMESPACE "ScreenStack"

class UUserWidget* UCOVEditorRuntimeLibrary::Create(UObject* WorldContextObject, TSubclassOf<class UUserWidget> WidgetType, APlayerController* OwningPlayer)
{
	//	The return result
	UUserWidget* screen = nullptr;

	if (WidgetType != nullptr)
	{
		//	Make sure the screen stack component exists in the player controller
		auto screenStack = OwningPlayer->GetHUD()->GetComponentByClass(UScreenStack::StaticClass());

		if (screenStack)
		{
			if (GIsEditor)
			{
				//	WHAT DO!?
			}

			if (OwningPlayer)
			{
				TSubclassOf<UScreen> screenType = WidgetType;
				screen = (UUserWidget*)(Cast<UScreenStack>(screenStack)->PushScreenByClass(screenType));
			}
			else if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			{
				//	We should really never get here
				//UUserWidget* screen = CreateWidget(World, WidgetType);

				check(true);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("The owning player controller does not have a screen stack component in its HUD. Unable to create and push a screen to a stack."));
			FMessageLog("PIE").Error(FText(LOCTEXT("ScreenStack", "The owning player controller's HUD does not have a screen stack component. Unable to create and push a screen to a stack.")))->AddToken(FUObjectToken::Create(OwningPlayer));
		}
	}

	return screen;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(UCOVEditorRuntime, ScreenStackRuntime)
