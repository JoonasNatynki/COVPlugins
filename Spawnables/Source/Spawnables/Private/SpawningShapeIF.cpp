#include "SpawningShapeIF.h"
#include "UE4Helpers.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"

const FVector ISpawningShapeIF::GetRandomPointInShapeComponent_Implementation(const bool bTryFindSurface) const
{
	const FVector RandLocationInShape = UE4CodeHelpers::FindRandomPointInsideShapeComponent(Cast<UShapeComponent>(this));

	if (bTryFindSurface)
	{
		const FHitResult Result = UE4CodeHelpers::SimpleTraceByChannel(
				Cast<UShapeComponent>(this),
				RandLocationInShape,
				RandLocationInShape + FVector(0.0f, 0.0f, -50.0f),
				ECC_WorldStatic,
				TEXT("Spawning shape component surface search"));

		if (Result.bBlockingHit)
		{
			return Result.ImpactPoint;
		}
	}

	return RandLocationInShape;
}

const bool ISpawningShapeIF::ConsumeSpawnSpace_Implementation(const FTransform& SpawnTransformInSpace,
	const FBox& SpawnBB)
{
	const FConsumedSpace ConsumedSpace(SpawnTransformInSpace, SpawnBB);
	ConsumedSpaces.Add(ConsumedSpace);
	
	return true;
}

FTransform ISpawningShapeIF::FindPlacementForBox(const UBoxComponent* BoxComponent, const FBox& BoxToFit) const
{
	FTransform ComponentTransform = BoxComponent->GetComponentTransform();
	FBox ComponentBounds(ComponentTransform.TransformPosition(-BoxComponent->GetUnscaledBoxExtent()), ComponentTransform.TransformPosition(BoxComponent->GetUnscaledBoxExtent()));

	FVector MinExtent = ComponentBounds.Min;
	FVector MaxExtent = ComponentBounds.Max - BoxToFit.GetExtent();

	std::vector<std::pair<FVector, FBox>> sortedConsumedSpaces;
	for (const FConsumedSpace& space : ConsumedSpaces) {
		FVector key = space.Transform.GetLocation();
		sortedConsumedSpaces.emplace_back(key, space.ConsumedBox.TransformBy(space.Transform));
	}
    
	// Sort consumed spaces based on their starting point along Z, then Y, then X axis
	std::sort(sortedConsumedSpaces.begin(), sortedConsumedSpaces.end(), [](const auto& a, const auto& b) {
		return a.first.Z != b.first.Z ? a.first.Z < b.first.Z :
			   (a.first.Y != b.first.Y ? a.first.Y < b.first.Y : a.first.X < b.first.X);
	});

	for (float z = MinExtent.Z; z <= MaxExtent.Z; z += 0.1f) {
		for (float y = MinExtent.Y; y <= MaxExtent.Y; y += 0.1f) {
			for (float x = MinExtent.X; x <= MaxExtent.X; x += 0.1f) {
				FTransform PossibleTransform(FQuat::Identity, FVector(x, y, z));
				FBox TransformedBoxToFit(BoxToFit.Min + PossibleTransform.GetTranslation(), BoxToFit.Max + PossibleTransform.GetTranslation());

				bool bOverlap = std::any_of(sortedConsumedSpaces.begin(), sortedConsumedSpaces.end(),
					[&TransformedBoxToFit](const auto& consumedSpace) {
						return consumedSpace.second.Intersect(TransformedBoxToFit);
					});

				if (!bOverlap) {
					return PossibleTransform;
				}
			}
		}
	}

	return FTransform(); // Return default transform if no space found
}