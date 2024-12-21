#include "Interactor.h"

UInteractor::UInteractor()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UInteractor::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractor::InitializeComponent()
{
	Super::InitializeComponent();
}
