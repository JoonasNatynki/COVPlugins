#include "SpawningShapeIF.h"
#include "UE4Helpers.h"
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
