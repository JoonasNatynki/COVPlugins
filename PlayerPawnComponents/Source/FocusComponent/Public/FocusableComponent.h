// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FocusableComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFocusable, All, Log)

//	A component meant for actors that are supposed to be focusable by a player. See FocusComponent.h for more information on how this component is used

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOCUSCOMPONENT_API UFocusableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFocusableComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty, FDefaultAllocator>& OutLifetimeProps) const override;

	UFUNCTION(Category = "Focusable", BlueprintCallable, BlueprintPure)
		FORCEINLINE bool IsFocusable() const;

	UFUNCTION(Category = "Focusable", BlueprintCallable, BlueprintPure)
		FORCEINLINE float GetFocusDistance() const;

	UFUNCTION(Category = "Focusable", BlueprintCallable)
		void SetIsFocusable(bool bIsFocusable);

private:
	UPROPERTY(Category = "Focusable", EditDefaultsOnly, Replicated)
		bool bCanBeFocusedAt = true;

	UPROPERTY(Category = "Focusable", EditAnywhere)
		//	The maximum distance this focusable can be focused at maximum by the actor (controlled pawn) that is doing the focusing.
		float FocusDistance = 300.0f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
};

FORCEINLINE bool UFocusableComponent::IsFocusable() const
{
	return bCanBeFocusedAt;
}

FORCEINLINE float UFocusableComponent::GetFocusDistance() const
{
	return FocusDistance;
}