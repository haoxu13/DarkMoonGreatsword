#pragma once

#include "Interaction.h"
#include "Material.h"
#include "Ray.h"
#include "CoreMinimal.h"

class FTriangle
{
public:
	FTriangle();
	FTriangle(const FVector& InPoint1, const FVector& InPoint2, const FVector& InPoint3);

	FVector operator[](int I) const
	{
		if (I == 0) return Point1;
		if (I == 1) return Point2;
		return Point3;
	}

	FVector& operator[](int I)
	{
		if (I == 0) return Point1;
		if (I == 1) return Point2;
		return Point3;
	}

	// Möller-Trumbore algorithm
	[[nodiscard]] FInteraction Intersect(const FRay& InRay, FTriangle* FromTriangle = nullptr) const;

	FVector GetCentroid() const;
	FVector GetNormal() const;
	Float GetArea() const;

	FVector LocalToWorld(const FVector& InUV) const;

public:
	FVector Point1, Point2, Point3;
};

class FTriangleMesh
{
public:
	explicit FTriangleMesh(const FString& InFilename, FMaterial* InMaterial = new FMaterial());
	explicit FTriangleMesh(const TArray<FTriangle>& NewTriangles, FMaterial* InMaterial = new FMaterial());

	[[nodiscard]] FInteraction Intersect(const FRay& InRay, FTriangle* FromTriangle) const;

	FInteraction SampleMesh() const;

protected:
	void LoadObjModelFromFile(const FString& InFilename);

public:
	FString Name;

protected:
	TArray<FTriangle> _Triangles;
	FMaterial* _Material;
};
