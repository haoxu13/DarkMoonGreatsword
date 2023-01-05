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

FInteraction FScene::Intersect(const FRay& InRay, FTriangleMesh* FromMesh) const
{
	FInteraction NewInteraction;

	float MinDistance = INFINITY;
	for (const FTriangleMesh* TriangleMesh : TriangleMeshes)
	{
		const FInteraction CurrentInteraction = TriangleMesh->Intersect(InRay, FromMesh);

		const bool bNearestIntersection = CurrentInteraction.bHappened && IsAlmostGreaterThanZero(CurrentInteraction.Distance) && CurrentInteraction.Distance < MinDistance;
		if (bNearestIntersection)
		{
			MinDistance = CurrentInteraction.Distance;
			NewInteraction = CurrentInteraction;
		}
	}

	return NewInteraction;
}

void FScene::SampleLight(FInteraction& OutSampleInteraction, float& OutPdf) const
{
	// TODO: UnCheat
	Light->SampleLight(OutSampleInteraction, OutPdf);
}
