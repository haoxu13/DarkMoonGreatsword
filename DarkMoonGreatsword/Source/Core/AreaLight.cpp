#include "AreaLight.h"

FAreaLight::FAreaLight(const FString& InFilename, FMaterial* InMaterial): FTriangleMesh(InFilename, InMaterial)
{
	InteractionInfo.bHappened = false;
	InteractionInfo.Emit = _Material->Emission;

	{
		float Area = 0.f;
		for (const FTriangle& Triangle : _Triangles)
		{
			Area  += Triangle.GetArea();
		}
		InverseArea = 1.f / Area;
	}

	if (!_Triangles.empty())
	{
		InteractionInfo.Normal = _Triangles[0].GetNormal();
	}

	InteractionInfo.Distance = INFINITY;
	InteractionInfo.HitMaterial = _Material;
	InteractionInfo.HitObject = this;
}

void FAreaLight::SampleLight(FInteraction& OutSampleInteraction, float& OutPdf) const
{
	const FInteraction MeshInteraction = SampleMesh();

	OutSampleInteraction = InteractionInfo;
	OutSampleInteraction.TCoords = MeshInteraction.TCoords;
	OutSampleInteraction.Coords = MeshInteraction.Coords;
	OutSampleInteraction.Normal = MeshInteraction.Normal;

	OutPdf = InverseArea;
}
