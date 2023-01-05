#pragma once

#include "Ray.h"
#include "CoreMinimal.h"
#include "TriangleMesh.h"

class FAreaLight;

class FScene
{
public:
	FScene(int InResolutionX, int InResolutionY);

	void Add(FTriangleMesh* InTriangleMesh);
	void AddLight(FAreaLight* NewLight);

	// Add from mesh to avoid intersection itself
	FInteraction Intersect(const FRay& InRay, FTriangleMesh* FromMesh = nullptr) const;

	void SampleLight(FInteraction& OutSampleInteraction, float& OutPdf) const;

public:
	int ResolutionX;
	int ResolutionY;

protected:
	TArray<FTriangleMesh*> TriangleMeshes;

	FAreaLight* Light;
};
