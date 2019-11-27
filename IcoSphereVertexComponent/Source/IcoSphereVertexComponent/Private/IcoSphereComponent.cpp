// Fill out your copyright notice in the Description page of Project Settings.

#include "IcoSphereComponent.h"
#include "UE4Helpers.h"

// Sets default values for this component's properties
UIcoSphereComponent::UIcoSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UIcoSphereComponent::BeginPlay()
{
	Super::BeginPlay();
}

FIndex UIcoSphereComponent::GetVertexForEdge(Lookup& lookup, VertexList& verticesIn, FIndex first, FIndex second)
{
	TPair<FIndex, FIndex> key(first, second);
	if (first > second)
	{
		key.Key = second;
		key.Value = first;
	}

	TArray<TPair<int32, int32>> keys;
	lookup.GetKeys(keys);

	bool bShouldMakeVertice = true;
	int32 midVertexIndex = -1;

	for (auto & keyt : keys)
	{
		if (keyt.Key == key.Key && keyt.Value == key.Value)
		{
			bShouldMakeVertice = false;
			midVertexIndex = *lookup.Find(keyt);
		}
	}

	if (bShouldMakeVertice)
	{
		lookup.Add(key, verticesIn.Num());
		auto& edge0 = verticesIn[first];
		auto& edge1 = verticesIn[second];
		auto point = (edge0 + edge1);
		point.Normalize();
		verticesIn.Add(point);

		return verticesIn.Num() - 1;
	}

	return midVertexIndex;
}

TriangleList UIcoSphereComponent::SubdivideIcoSphereMesh(VertexList& verticesIn, const TriangleList& trianglesIn)
{
	Lookup lookup;
	TriangleList result;

	for (auto & each : trianglesIn)
	{
		TArray<FIndex> mid;
		for (int edge = 0; edge < 3; ++edge)
		{
			mid.Add(GetVertexForEdge(lookup, verticesIn,
				each.vertex[edge], each.vertex[(edge + 1) % 3]));
		}

		result.Add({ each.vertex[0], mid[0], mid[2] });
		result.Add({ each.vertex[1], mid[1], mid[0] });
		result.Add({ each.vertex[2], mid[2], mid[1] });
		result.Add({ mid[0], mid[1], mid[2] });
	}

	return result;
}

void UIcoSphereComponent::GenerateIcoSphere(int32 IcoSphereSubdivisionsIn)
{
	MeshVertices = GenerateIcoSphere_Internal(IcoSphereSubdivisionsIn).Key;
}

IndexedMesh UIcoSphereComponent::GenerateIcoSphere_Internal(int32 subdivisions)
{
	for (int i = 0; i < subdivisions; ++i)
	{
		triangles = SubdivideIcoSphereMesh(vertices, triangles);
	}
	IndexedMesh temp;
	temp.Key = vertices;
	temp.Value = triangles;

	COV_LOG(LogTemp, Log, TEXT("Icosphere generated with (%d) subdivisions."), IcoSphereSubdivisions);
	return temp;
}

// Called every frame
void UIcoSphereComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

