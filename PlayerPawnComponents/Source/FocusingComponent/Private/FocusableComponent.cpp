#include "FocusableComponent.h"
#include "FocusingComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY(LogFocusable)

// Sets default values for this component's properties
UFocusableComponent::UFocusableComponent(const FObjectInitializer& ObjInit)
	:Super(ObjInit)
{
	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

void UFocusableComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UFocusableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	RemoveAllFocusingComponents();
}

bool UFocusableComponent::IsFocusable(const UFocusingComponent* FocusingComp) const
{
	return IsActive() && HasBegunPlay() && IsFocusableIgnoreDistance(FocusingComp);
}

bool UFocusableComponent::IsFocusableIgnoreDistance(const UFocusingComponent* FocusingComp) const
{
	// ignore Active flag if DistanceMethod is Trigger as the flag is flipped
	// based on whether player is inside the trigger or not
	if ((DistanceMethod == EFocusableDistanceMethod::Trigger || IsActive()) && FocusBlockers.IsEmpty())
	{
		for (UActorComponent* Condition : CachedConditions)
		{
			if (IsValid(Condition) &&
				Condition->IsActive())
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool UFocusableComponent::IsFocusableIgnoreDistance(const APawn* Pawn) const
{
	if (Pawn)
	{
		if (UFocusingComponent* FocusingComp = Pawn->FindComponentByClass<UFocusingComponent>())
		{
			return IsFocusableIgnoreDistance(FocusingComp);
		}
	}

	return false;
}

bool UFocusableComponent::IsCurrentlyFocusedAtleastBySomeone() const
{
	return FocusingComponents.Num() > 0;
}

bool UFocusableComponent::IsCurrentlyFocusedAtleastByOneLocalPlayer() const
{
	for(TWeakObjectPtr<UFocusingComponent> FocusingComp : GetFocusingComponents())
	{
		if(FocusingComp.IsValid())
		{
			if (const APawn* AsPawn = Cast<APawn>(FocusingComp->GetOwner()))
			{
				if (const AController* Controller = AsPawn->GetController())
				{
					return Controller->IsLocalPlayerController();
				}
			}
		}
	}

	return false;
}

void UFocusableComponent::SetFocusable(FName Context, bool bIsFocusable)
{
	if (bIsFocusable)
	{
		FocusBlockers.Remove(Context);
	}
	else
	{
		FocusBlockers.Add(Context);
	}

	if (IsFocusBlocked())
	{
		RemoveAllFocusingComponents();
	}
	
	UE_LOG(LogFocusable, Log, TEXT("(%s) set as %s by %s."), *GetNameSafe(GetOwner()), (bIsFocusable ? (TEXT("FOCUSABLE")) : (TEXT("UNFOCUSABLE"))), *Context.ToString());
}

bool UFocusableComponent::IsFocusBlocked() const
{
	return FocusBlockers.Num() > 0;
}

TSet<TWeakObjectPtr<UFocusingComponent>> UFocusableComponent::GetFocusingComponents() const
{
	return FocusingComponents;
}

void UFocusableComponent::AddFocusingPlayer(UFocusingComponent* NewFocusingComponent)
{
	FocusingComponents.Add(NewFocusingComponent);
	UE_LOG(LogFocusable, Verbose, TEXT("Actor (%s) has gained focus on (%s)"), *GetNameSafe(NewFocusingComponent->GetOwner()), *GetNameSafe(GetOwner()));
	OnFocusGained.Broadcast(this, NewFocusingComponent);
	OnFocusablesChanged.Broadcast(this, FocusingComponents.Num() > 0);
}

bool UFocusableComponent::RemoveFocusingPlayer(UFocusingComponent* NewFocusingComponent)
{
	const bool bSuccess = FocusingComponents.Remove(NewFocusingComponent) > 0;
	UE_LOG(LogFocusable, Verbose, TEXT("Actor (%s) has lost focus on (%s)"), *GetNameSafe(NewFocusingComponent), *GetNameSafe(GetOwner()));
	OnFocusLost.Broadcast(this, NewFocusingComponent);
	OnFocusablesChanged.Broadcast(this, FocusingComponents.Num() > 0);
	return bSuccess;
}

void UFocusableComponent::RemoveAllFocusingComponents()
{
	for (TWeakObjectPtr<UFocusingComponent> FocusingComponent : GetFocusingComponents())
	{
		OnFocusLost.Broadcast(this, FocusingComponent.Get());
	}

	OnFocusLost.Broadcast(this, nullptr);
	OnFocusablesChanged.Broadcast(this, false);
	
	FocusingComponents.Empty();
}

void UFocusableComponent::OnCycleRestarted()
{
	RemoveAllFocusingComponents();
}

float UFocusableComponent::GetFocusDistance() const
{
	return FocusableDistance;
}