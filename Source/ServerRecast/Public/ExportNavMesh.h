// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "Runtime/Engine/Public/AI/Navigation/RecastNavMeshGenerator.h"
//#include "ExportNavMesh.generated.h"
/**
*
*/

struct FServerRecastGeometryCache
{
	struct FHeader
	{
		int32 NumVerts;
		int32 NumFaces;
		struct FWalkableSlopeOverride SlopeOverride;
	};

	FHeader Header;

	/** recast coords of vertices (size: NumVerts * 3) */
	float* Verts;

	/** vert indices for triangles (size: NumFaces * 3) */
	int32* Indices;

	FServerRecastGeometryCache() {}
	FServerRecastGeometryCache(const uint8* Memory);
};

class SERVERRECAST_API FExportNavMesh : public FRecastNavMeshGenerator
{

public:
	void MyExportNavigationData(const FString& FileName);

	void GrowConvexHull(const float ExpandBy, const TArray<FVector>& Verts, TArray<FVector>& OutResult);

	void TransformVertexSoupToRecast(const TArray<FVector>& VertexSoup, TNavStatArray<FVector>& Verts, TNavStatArray<int32>& Faces);

	void ExportGeomToOBJFile(const FString& InFileName, const TNavStatArray<float>& GeomCoords, const TNavStatArray<int32>& GeomFaces, const FString& AdditionalData);

	static FVector ChangeDirectionOfPoint(FVector Coord);
};
