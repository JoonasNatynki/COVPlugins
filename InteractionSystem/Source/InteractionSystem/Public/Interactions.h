#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactions.generated.h"

UCLASS( ClassGroup=(Interactions), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API UInteractions : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractions();

	virtual void InitializeComponent() override;

protected:
	virtual void BeginPlay() override;
};
