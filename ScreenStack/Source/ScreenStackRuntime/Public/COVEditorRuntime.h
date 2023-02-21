#pragma once
#include "CoreMinimal.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include "COVEditorRuntime.generated.h"

class UCOVEditorRuntime : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

//	Blueprint function library class
UCLASS()
class SCREENSTACKRUNTIME_API UCOVEditorRuntimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (WorldContext = "WorldContextObject", DisplayName = "Push a screen by class to the stack", BlueprintInternalUseOnly = "true"), Category = "Widget")
		static class UUserWidget* Create(UObject* WorldContextObject, TSubclassOf<class UUserWidget> WidgetType, APlayerController* OwningPlayer);
};