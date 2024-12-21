#include "Interactions.h"

UInteractions::UInteractions()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UInteractions::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInteractions::BeginPlay()
{
	Super::BeginPlay();
}
