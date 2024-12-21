#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactor.generated.h"

UCLASS( ClassGroup=(Interactions), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractor();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
};
