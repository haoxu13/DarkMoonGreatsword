#include "AreaLight.h"

FAreaLight::FAreaLight(const FString& InFilename, FMaterial* InMaterial): FTriangleMesh(InFilename, InMaterial)
{
	InteractionInfo.bHappened = false;
	InteractionInfo.Emit = _Material->Emission;

	{
		Area = 0.0;
		for (const FTriangle& Triangle : _Triangles)
		{
			Area += Triangle.GetArea();
		}
		InverseArea = 1.0 / Area;
	}

	if (!_Triangles.empty())
	{
		InteractionInfo.Normal = _Triangles[0].GetNormal();
	}

	InteractionInfo.Distance = INFINITY;
	InteractionInfo.HitMaterial = _Material;
}

void FAreaLight::SampleLight(FInteraction& OutSampleInteraction, Float& OutPdf) const
{
	const FInteraction MeshInteraction = SampleMesh();

	OutSampleInteraction = InteractionInfo;
	OutSampleInteraction.TCoords = MeshInteraction.TCoords;
	OutSampleInteraction.Coords = MeshInteraction.Coords;
	OutSampleInteraction.Normal = MeshInteraction.Normal;
	OutSampleInteraction.HitTriangle = MeshInteraction.HitTriangle;

	OutPdf = InverseArea;
}
