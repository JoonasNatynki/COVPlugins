// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IcoSphereComponent.generated.h"

USTRUCT()
struct FTriangle
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		int32 vertex[3];
};

using FIndex = int32;

using TriangleList = TArray<FTriangle>;
using VertexList = TArray<FVector>;
using Lookup = TMap<TPair<FIndex, FIndex>, FIndex>;
using IndexedMesh = TPair<VertexList, TriangleList>;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class ICOSPHEREVERTEXCOMPONENT_API UIcoSphereComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int32 IcoSphereSubdivisions = 2;
	
	//	The generated icosphere
	TArray<FVector> MeshVertices;

	FIndex GetVertexForEdge(Lookup& lookup, VertexList& vertices, FIndex first, FIndex second);
	TriangleList SubdivideIcoSphereMesh(VertexList& vertices, const TriangleList& triangles);
	IndexedMesh GenerateIcoSphere_Internal(int32 subdivisions);
	//	Initial values
	float X = .525731112119133606f;
	float Z = .850650808352039932f;
	float N = 0.f;

	//	The platonic solid base mesh vertices
	VertexList 	vertices =
	{
	  FVector(-X,N,Z), FVector(X,N,Z), FVector(-X,N,-Z), FVector(X,N,-Z),
	  FVector(N,Z,X), FVector(N,Z,-X), FVector(N,-Z,X), FVector(N,-Z,-X),
	  FVector(Z,X,N), FVector(-Z,X, N), FVector(Z,-X,N), FVector(-Z,-X, N)
	};

	//	The edge indices of the platonic solid
	TriangleList triangles =
	{
	  {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	  {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	  {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	  {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};

public:
	// Sets default values for this component's properties
	UIcoSphereComponent();

	UFUNCTION(Category = "Icosphere", BlueprintCallable, BlueprintPure)
		TArray<FVector>& GetMesh() { return MeshVertices; }

	UFUNCTION(Category = "Icosphere", BlueprintCallable)
		void GenerateIcoSphere(int32 SubDivisionCount);
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
