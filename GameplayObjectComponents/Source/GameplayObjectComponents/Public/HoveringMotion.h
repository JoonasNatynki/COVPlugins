// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoveringMotion.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHoveringMotion, Log, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYOBJECTCOMPONENTS_API UHoveringMotion : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoveringMotion();

	UPROPERTY()
		//	The hovering mesh of the actor
		USceneComponent* ComponentToHover;



	UPROPERTY(Category = "Hovering Motion", EditAnywhere)
		//	If the mesh will rotate
		bool bRotate = true;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bRotate"))
		float XAxisRotationSpeed = 0.26f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bRotate"))
		float YAxisRotationSpeed = -0.2f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bRotate"))
		float ZAxisRotationSpeed = 0.2f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bRotate"))
		//	If the mesh will rotate around z axis
		bool bRandomizeInitialRotation = true;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bRotate"))
		//	If TRUE: will randomize the directions of the rotations but not the speeds
		bool bRandomizeRotationDirections = true;


	UPROPERTY(Category = "Hovering Motion", EditAnywhere)
		//	If the mesh will hover
		bool bHoverMovement = true;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bHoverMovement"))
		float HoverXMovementDistance = 0.0f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bHoverMovement"))
		float HoverYMovementDistance = 0.0f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bHoverMovement"))
		float HoverZMovementDistance = 20.0f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bHoverMovement"))
		float HoverRepeatFrequency = 1.0f;

	UPROPERTY(Category = "Hovering Motion", EditAnywhere, meta = (EditCondition = "bHoverMovement"))
		//	If TRUE: different objects that hover with the same frequency will not hover in sync
		bool bRandomizeHoverFrequencyInitialStartPhase = true;



	UPROPERTY(Category = "Hovering Motion", EditAnywhere)
		//	Whether to only animate the object locally regardless of replication conditions. If the object has replicate movement enabled, this will cause the object transform to be different to what it is on the server.
		bool bAnimateOnlyLocally = false;



	UFUNCTION(Category = "Hovering Motion", BlueprintCallable)
		void SetHoveringComponent(USceneComponent* _componentToHover);

	UFUNCTION(Category = "Hovering Motion", BlueprintCallable)
		void SetAnimating(bool bShouldAnimate);

	UFUNCTION(Category = "Hovering Motion", BlueprintCallable, BlueprintPure)
		FORCEINLINE bool IsHoverComponentRootComponent() const;


	void UpdateMeshTransform(float deltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsRotatingRootComponent = false;	//	If the component is rotating the root mesh. This determines if its just a local hovering transformation or the actual actors world location. This is expensive if simulated over the network
	bool bIsReplicatingMovementOverNetwork = false;		//	If the component is rotating the root mesh, it's important to know if the object is replicating movement over the network so that only the authority animates the root component (as its movement is then replicated over the network to listening clients. We don't want the clients to fight the authority on this.
	bool bIsAnimating = true;

	//	Used for bRandomizeHoverFrequencyInitialStartPhase
	float InitialHoverOffset = 0.0f;

private:

	//	Sets component to hover to be the root component of this component's owner and sets it to animate instead.
	void DefaultToRootComponentAnimation_Internal();
	void RandomizeInitialRotation_Internal();
	void RandomizeInitialRotationDirections_Internal();

	//	Checks if necessary things are initialized elsewhere, if not, just default to default initialization and start hovering.
	void DefaultToDefaultInitialization_Internal();
	bool bInitialized = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

FORCEINLINE bool UHoveringMotion::IsHoverComponentRootComponent() const
{
	return GetOwner()->GetRootComponent() == ComponentToHover;
}