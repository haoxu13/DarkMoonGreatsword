#include "Integrator.h"

#include <execution>
#include <iostream>

#include "Ray.h"
#include "Scene.h"
#include "Utility.h"

inline Float Deg2Rad(const Float InDeg) { return InDeg * PI / 180.0; }

void FPathIntegrator::Render(const FScene& InScene)
{
	const int& ResolutionX = InScene.ResolutionX;
	const int& ResolutionY = InScene.ResolutionY;

	_ResolutionX = ResolutionX;
	_ResolutionY = ResolutionY;

	int Resolution = ResolutionX * ResolutionY;

	Float Fov = 40.0;
	TArray<FVector> NewFramebuffer(ResolutionX * ResolutionY);

	Float Scale = tan(Deg2Rad(Fov * 0.5));
	Float ImageAspectRatio = static_cast<Float>(ResolutionX) / static_cast<Float>(ResolutionY);
	FVector EyePos(278, 273, -800);

	std::cout << "SPP: " << SamplesPerPixel << "\n";

	std::atomic<int> FinishedPixelsCount{0};
#pragma omp parallel for
	for (int CurrentIndex = 0; CurrentIndex < static_cast<int>(NewFramebuffer.size()); ++CurrentIndex)
	{
		const int IndexX = CurrentIndex % ResolutionY;
		const int IndexY = CurrentIndex / ResolutionY;
		const uint32_t PixelIndex = IndexY * ResolutionX + IndexX;

		for (int NthSample = 0; NthSample < SamplesPerPixel; NthSample++)
		{
			// Generate primary ray direction
			FVector ViewDirection;
			{
				const Float RandomBiasX = GetRandomFloat(-0.5, 0.5);
				const Float RandomBiasY = GetRandomFloat(-0.5, 0.5);
				const Float DeviceCoordX = (2.0 * (static_cast<Float>(IndexX) + 0.5 + RandomBiasX) / static_cast<Float>(ResolutionX) - 1.0) *
					ImageAspectRatio * Scale;
				const Float DeviceCoordY = (1.0 - 2.0 * (static_cast<Float>(IndexY) + 0.5 + RandomBiasY) / static_cast<Float>(ResolutionY)) * Scale;
				ViewDirection = FVector(-DeviceCoordX, DeviceCoordY, 1).Normalize();
			}
			NewFramebuffer[PixelIndex] += Shade(FRay(EyePos, ViewDirection), InScene, 0) * InverseSamplesPerPixel;
		}

		// Report progress on each pixel
		{
			++FinishedPixelsCount;
			const Float CurrentProgress = 100.0 * static_cast<Float>(FinishedPixelsCount) / static_cast<Float>(Resolution);
			printf("\rRender progress: %f%%", CurrentProgress);
			fflush(stdout);
		}
	}

	Framebuffer = NewFramebuffer;
}

FVector FPathIntegrator::Shade(const FRay& InRay, const FScene& InScene, int Depth)
{
	// Check hit point
	FInteraction ShadingPointInteraction = InScene.Intersect(InRay);

	// Ray missed hit
	if (!ShadingPointInteraction.bHappened)
	{
		return FVector();
	}

	// Hit light source, assuming light source won't reflect radiance
	if (ShadingPointInteraction.Emit.Norm() > 0.0)
	{
		return ShadingPointInteraction.Emit;
	}

	const FVector ViewRayDirection = Normalize(-InRay.Direction); // Pointing outwards from shading point
	const FVector ShadingPointPosition = ShadingPointInteraction.Coords;
	const FVector ShadingPointNormal = Normalize(ShadingPointInteraction.Normal);

	// Sample direct light
	FVector DirectLightRadiance;
	{
		FInteraction DirectLightInteraction;
		Float PdfLight; // Not used
		// TODO: Sample multiple lights
		InScene.SampleLight(DirectLightInteraction, PdfLight);

		const FVector LightPosition = DirectLightInteraction.Coords;
		FVector LightDirection = Normalize(LightPosition - ShadingPointPosition); // Pointing outwards from shading point
		FVector DirectLightNormal = Normalize(DirectLightInteraction.Normal);

		// Check occlusion
		FInteraction NearestIntersectionToLight = InScene.Intersect(FRay(ShadingPointPosition, LightDirection), ShadingPointInteraction.HitTriangle);
		if (FVector::IsAlmostSame(NearestIntersectionToLight.Coords, DirectLightInteraction.Coords))
		{
			const Float Costheta = DotProduct(LightDirection, ShadingPointNormal); // Angle of surface normal and SurfaceToLight direction
			const Float CosthetaPrime = DotProduct(-LightDirection, DirectLightNormal); // Angle of light normal and LightToSurface direction
			if (Costheta > 0.0 && CosthetaPrime > 0.0)
			{
				// Assuming shading point won't emit
				// EmitRadiance(0) + LightRadiance * BRDF * Costheta * Costheta' / LightPositionDistanceSquare / LightArea
				const FVector BRDF = ShadingPointInteraction.HitMaterial->Eval(LightDirection, ViewRayDirection, ShadingPointNormal);
				const FVector InSampleLightRadiance = DirectLightInteraction.Emit;
				const Float InverseNormSquare = 1.0 / ((LightPosition - ShadingPointPosition).Norm() * (LightPosition - ShadingPointPosition).Norm());
				const Float InverseLightPdf = InScene.InverseLightPdf;

				DirectLightRadiance = InSampleLightRadiance * BRDF * Costheta * CosthetaPrime * InverseNormSquare * InverseLightPdf;
			}
		}
	}

	if constexpr (!SampleIndirectLight)
	{
		return DirectLightRadiance;
	}

	// Stop condition
	if (GetRandomFloat() >= RussianRoulette)
	{
		return DirectLightRadiance;
	}

	// Sample Indirect light
	FVector IndirectLightRadiance;
	{
		const FVector IndirectLightDirection = ShadingPointInteraction.HitMaterial->Sample(ViewRayDirection, ShadingPointNormal);
		const Float Costheta = DotProduct(IndirectLightDirection, ShadingPointNormal);
		assert(Costheta >= 0.0);
		constexpr Float InverseHemiSpherePdf = 2.0 * PI;
		const FVector InRadiance = Shade(FRay(ShadingPointPosition, IndirectLightDirection), InScene, Depth + 1);
		const FVector BRDF = ShadingPointInteraction.HitMaterial->Eval(IndirectLightDirection, ViewRayDirection, ShadingPointNormal);

		IndirectLightRadiance = InRadiance * BRDF * Costheta * InverseHemiSpherePdf * InverseRussianRoulette;
	}

	return DirectLightRadiance + IndirectLightRadiance;
}
