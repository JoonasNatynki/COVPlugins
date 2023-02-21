// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenStack.generated.h"

class APlayerController;

class FScreenStackModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	GameOnly,
	GameAndUI,
	UIOnly
};

DECLARE_LOG_CATEGORY_EXTERN(ScreenStack, Log, All)

class UScreen;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginDestroy, UScreen*, screen);

UCLASS()
class SCREENSTACK_API UScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	UScreen(const FObjectInitializer& ObjInit);

	UPROPERTY(Category = "Screen", EditAnywhere)
		//	Is this screen being forced to stay in stack? Screen can not be removed, only hidden.
		bool bScreenIsLocked = false;

	UPROPERTY(Category = "Screen", EditDefaultsOnly)
		//	Screens that are below in the stack will be visible. Note: If the screen below is an overlay, the visibility will stop there.
		bool bScreenIsAnOverlay = false;

	UPROPERTY(Category = "Screen", EditDefaultsOnly)
		//	If there can exist more than one of these screens at once. If you push a second screen of the same type, the existing screen will be moved to the top of the stack instead.
		bool bAllowMultipleInstances = false;

	UPROPERTY(Category = "Screen", EditDefaultsOnly, meta = (EditCondition = "!bAllowMultipleInstances"))
		//	Instead of moving the existing screen to the top of the stack, replace the screen entirely instead.
		bool bOverrideExistingScreen = true;

	UPROPERTY(Category = "Screen", EditDefaultsOnly)
		//	Should the game or UI consume input, or both if possible?
		EInputMode InputMode = EInputMode::GameOnly;

	UPROPERTY(Category = "Screen", EditDefaultsOnly)
		//	If mouse cursor is shown for mouse input
		bool bShowMouseCursor = false;

	UPROPERTY(Category = "Screen", EditDefaultsOnly, meta = (EditCondition = "bShowMouseCursor"))
		EMouseLockMode MouseLockMode = EMouseLockMode::LockAlways;

	UPROPERTY(Category = "Screen", EditDefaultsOnly)
		//	Bind a key to automatically close the screen with
		FKey KeyToCloseScreenWith;




	UFUNCTION(Category = "Screen", BlueprintCallable, BlueprintPure)
		//	Is the screen locked in place and can't be removed from stack?
		bool GetHasScreenLock() const { return bScreenIsLocked; };

	UFUNCTION(Category = "Screen", BlueprintCallable)
		// Locks the screen so that it can't be removed from the stack.
		void LockScreen() { bScreenIsLocked = true; };

	UFUNCTION(Category = "Screen", BlueprintCallable)
		// Release lock for this window so that it can be removed from the stack.
		void ReleaseLock() { bScreenIsLocked = false; };

	UFUNCTION(Category = "Screen", BlueprintCallable, BlueprintPure)
		//	Is the screen locked in place and can't be removed from stack?
		bool GetIsScreenLocked() const { return bScreenIsLocked; };

	UFUNCTION(Category = "Screen", BlueprintCallable, BlueprintPure)
		//	Is the screen an overlay?
		bool GetIsScreenAnOverlay() const { return bScreenIsAnOverlay; };

	UFUNCTION(Category = "Screen", BlueprintCallable, BlueprintPure)
		//	Can more than one screen exist at the same time in the stack?
		bool GetAllowMultipleInstances() const { return bAllowMultipleInstances; };

	UPROPERTY()
		FOnBeginDestroy OnbeginDestroy;

	void RemoveInputMode();
	void ApplyInputMode();

	//	Bind button to close the screen
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	bool bScreenStackManagerChangesVisibility = false;
	ESlateVisibility OutsideVisibilityOverride = ESlateVisibility::SelfHitTestInvisible;	//	Basically tells you if something else wanted to hide this screen or not
	virtual void SetVisibility(ESlateVisibility visibility) override;
	virtual void RemoveFromParent() override;

private:
	bool bOriginalShowMouseCursor = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenRemovedFromStack, UScreen*, RemovedScreen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenPushedTostack, UScreen*, PushedScreen);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class SCREENSTACK_API UScreenStack : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UScreenStack();

	UPROPERTY()
		TArray<UScreen*> screenStack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void UpdateScreenStackVisibilities_Internal();

	//	This function handles screen visibility properly for screens
	void SetScreenVisibility(UScreen* screen, const ESlateVisibility Visibility) const;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Category = "Screen", BlueprintAssignable)
		FOnScreenRemovedFromStack OnScreenRemoval;
	UPROPERTY(Category = "Screen", BlueprintAssignable)
		FOnScreenPushedTostack OnScreenPushed;


	UFUNCTION(Category = "Screen", BlueprintCallable, BlueprintPure)
		APlayerController* GetOwnerPlayerController() const;

	//UFUNCTION(Category = "Screen", BlueprintCallable, meta = (DeterminesOutputType = "screenType"))
		UObject* PushScreenByClass(const TSubclassOf<UScreen> screenType);

	UFUNCTION(Category = "Screen", BlueprintCallable)
		bool PopTopScreen();

	UFUNCTION(Category = "Screen", BlueprintCallable)
		UScreen* GetTopMostScreen() const;

	UFUNCTION(Category = "Screen", BlueprintCallable)
		//	Remove a screen from the stack
		bool PopScreen(UScreen* screen);

	UFUNCTION(Category = "Screen", BlueprintCallable, meta = (DeterminesOutputType = "screenType"))
		//	Find a screen of the type in the stack, if any.
		TArray<UScreen*> FindScreensOfType(const TSubclassOf<UScreen> screenType) const;

	UFUNCTION(Category = "Screen", BlueprintCallable, meta = (DeterminesOutputType = "screenType"))
		//	Find a screen of the type in the stack, if any.
		TArray<UScreen*> GetScreensOfType(const TSubclassOf<UScreen> screenType) const;

	UFUNCTION(Category = "Screen", BlueprintCallable)
		bool HasScreen(const UScreen* screen) const;

	UFUNCTION()
		void RemoveScreenFromStackOnRemoveFromParent(UScreen* screen);

	UScreen* CreateScreen_Internal(const TSubclassOf<UScreen> type) const;
	void PushScreenToStack_Internal(UScreen* const screen);
	bool PopScreen_Internal(UScreen* screen);	//	This version removes the screen from the viewport

private:

	//	Screens that wait to be added to viewport. This is done because the K2 node that calls the pushscreenbyclass function only initializes the default parameters after the screen has already run Construct if added to viewport first.
	TArray<UScreen*> screensWaitingToBeAddedToviewport;
};