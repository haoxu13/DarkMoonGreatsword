#include "Scene.h"
#include "AreaLight.h"

FScene::FScene(int InResolutionX, int InResolutionY) :
	ResolutionX(InResolutionX),
	ResolutionY(InResolutionY)
{
}

void FScene::Add(FTriangleMesh* InTriangleMesh)
{
	TriangleMeshes.emplace_back(InTriangleMesh);
}

void FScene::AddLight(FAreaLight* NewLight)
{
	Light = NewLight;
	Add(NewLight);
}

FInteraction FScene::Intersect(const FRay& InRay, FTriangle* FromTriangle) const
{
	FInteraction NewInteraction;

	Float MinDistance = INFINITY;
	for (const FTriangleMesh* TriangleMesh : TriangleMeshes)
	{
		const FInteraction CurrentInteraction = TriangleMesh->Intersect(InRay, FromTriangle);

		const bool bNearestIntersection = CurrentInteraction.bHappened && CurrentInteraction.Distance > 0.0 && CurrentInteraction.Distance < MinDistance;
		if (bNearestIntersection)
		{
			MinDistance = CurrentInteraction.Distance;
			NewInteraction = CurrentInteraction;
		}
	}

	return NewInteraction;
}

void FScene::SampleLight(FInteraction& OutSampleInteraction, Float& OutPdf) const
{
	// TODO: UnCheat
	Light->SampleLight(OutSampleInteraction, OutPdf);
}
