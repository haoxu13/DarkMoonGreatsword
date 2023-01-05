#include "TriangleMesh.h"

#include <tiny_obj_loader.h>

#include <unordered_map>

FTriangle::FTriangle()
{
}

FTriangle::FTriangle(const FVector& InPoint1, const FVector& InPoint2, const FVector& InPoint3) :
	Point1(InPoint1),
	Point2(InPoint2),
	Point3(InPoint3)
{
}

FInteraction FTriangle::Intersect(const FRay& InRay) const
{
	// Möller-Trumbore
	FInteraction NewInteraction;

	FVector NewOrigin = InRay.Origin - Point1;
	FVector Edge1 = Point2 - Point1;
	FVector Edge2 = Point3 - Point1;

	float Determinant = InRay.Direction.CrossProduct(Edge2).DotProduct(Edge1);

	float DeterminantT = NewOrigin.CrossProduct(Edge1).DotProduct(Edge2);
	float DeterminantU = InRay.Direction.CrossProduct(Edge2).DotProduct(NewOrigin);
	float DeterminantV = NewOrigin.CrossProduct(Edge1).DotProduct(InRay.Direction);

	float OutT = DeterminantT / Determinant;
	float OutU = DeterminantU / Determinant;
	float OutV = DeterminantV / Determinant;

	const bool bHit = IsAlmostGreaterThanZero(OutT) && IsAlmostInRange(OutU) && IsAlmostInRange(OutV) && IsAlmostSmallerThanOne(OutU + OutV);

	if (bHit)
	{
		NewInteraction.bHappened = bHit;
		NewInteraction.Coords = InRay.Origin + OutT * InRay.Direction;
		NewInteraction.TCoords = FVector(OutU, OutV, 0.f);
		NewInteraction.Normal = Edge1.CrossProduct(Edge2).Normalize();
		NewInteraction.Distance = OutT;
	}

	return NewInteraction;
}

FVector FTriangle::GetCentroid() const
{
	return 1.f / 3.f * (Point1 + Point2 + Point3);
}

FVector FTriangle::GetNormal() const
{
	const FVector Edge1 = Point2 - Point1;
	const FVector Edge2 = Point3 - Point1;
	return Edge1.CrossProduct(Edge2).Normalize();
}

float FTriangle::GetArea() const
{
	const FVector Edge1 = Point2 - Point1;
	const FVector Edge2 = Point3 - Point1;

	return std::fabs(Edge1.CrossProduct(Edge2).Norm() * 0.5f);
}

FVector FTriangle::LocalToWorld(const FVector& InUV) const
{
	const FVector Edge1 = Point2 - Point1;
	const FVector Edge2 = Point3 - Point1;

	return Point1 + InUV.X * Edge1 + InUV.Y * Edge2;
}

FTriangleMesh::FTriangleMesh(const FString& InFilename, FMaterial* InMaterial) :
	_Material(InMaterial),
	Name(InFilename)
{
	LoadObjModelFromFile(InFilename);
}

FTriangleMesh::FTriangleMesh(const TArray<FTriangle>& NewTriangles, FMaterial* InMaterial) :
	_Triangles(NewTriangles),
	_Material(InMaterial)
{
}

FInteraction FTriangleMesh::Intersect(const FRay& InRay, FTriangleMesh* FromMesh) const
{
	FInteraction NewInteraction;

	// Don't intersect with myself- 
	if (FromMesh && FromMesh == this)
	{
		return NewInteraction;
	}

	float MinDistance = INFINITY;
	for (const auto& Triangle : _Triangles)
	{
		const FInteraction CurrentInteraction = Triangle.Intersect(InRay);

		const bool bNearestIntersection = CurrentInteraction.bHappened && IsAlmostGreaterThanZero(CurrentInteraction.Distance) && CurrentInteraction.Distance < MinDistance;
		if (bNearestIntersection)
		{
			MinDistance = CurrentInteraction.Distance;
			NewInteraction = CurrentInteraction;
			NewInteraction.HitMaterial = _Material;
			NewInteraction.Emit = _Material->Emission;
			NewInteraction.HitObject = const_cast<FTriangleMesh*>(this);
		}
	}

	return NewInteraction;
}

FInteraction FTriangleMesh::SampleMesh() const
{
	assert(!_Triangles.empty());

	const int RandomTriangleIndex = GetRandomIntInRange(0, static_cast<int>(_Triangles.size()) - 1);
	const float RandomU = GetRandomFloat();
	const float RandomV = 1.f - RandomU;
	const FVector RandomUV(RandomU, RandomV, 0.f);
	// const FVector RandomUV(GetRandomFloat(), GetRandomFloat(), 0.f);

	const FVector SamplePosition = _Triangles[RandomTriangleIndex].LocalToWorld(RandomUV);

	FInteraction ReturnSampleInteraction;
	ReturnSampleInteraction.TCoords = RandomUV;
	ReturnSampleInteraction.Coords = SamplePosition;
	ReturnSampleInteraction.Normal = _Triangles[RandomTriangleIndex].GetNormal();
	ReturnSampleInteraction.HitObject = const_cast<FTriangleMesh*>(this);
	ReturnSampleInteraction.HitMaterial = _Material;

	return ReturnSampleInteraction;
}

void FTriangleMesh::LoadObjModelFromFile(const FString& InFilename)
{
	tinyobj::attrib_t Attrib;
	std::vector<tinyobj::shape_t> Shapes;
	std::vector<tinyobj::material_t> Materials;
	std::string Warn, Err;

	if (!tinyobj::LoadObj(&Attrib, &Shapes, &Materials, &Warn, &Err, GetAssetPath(InFilename).string().c_str()))
	{
		throw std::runtime_error(Warn + Err);
	}

	for (auto& Shape : Shapes)
	{
		size_t IndexOffset = 0;
		// For each face
		for (size_t FaceIndex = 0; FaceIndex < Shape.mesh.num_face_vertices.size(); FaceIndex++)
		{
			const size_t VertexNum = Shape.mesh.num_face_vertices[FaceIndex];

			FTriangle NewTriangle;
			// For each vertex in the face
			for (size_t VertexIndex = 0; VertexIndex < VertexNum; VertexIndex++)
			{
				tinyobj::index_t Index = Shape.mesh.indices[IndexOffset + VertexIndex];
				FVector NewPoint
				{
					Attrib.vertices[3 * Index.vertex_index + 0],
					Attrib.vertices[3 * Index.vertex_index + 1],
					Attrib.vertices[3 * Index.vertex_index + 2],
				};
				NewTriangle[VertexIndex] = NewPoint;
			}

			IndexOffset += VertexNum;
			_Triangles.push_back(NewTriangle);
		}
	}
}
