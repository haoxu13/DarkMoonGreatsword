#pragma once

#include "CoreMinimal.h"
#include "Ray.h"

class FScene;

class FPathIntegrator
{
public:
	void Render(const FScene& InScene);

	FVector Shade(const FRay& InRay, const FScene& InScene, int Depth);

	// Possibility of a lambert surface keep sampling indirect light
	static constexpr Float RussianRoulette{0.8};
	static constexpr Float InverseRussianRoulette{1.0 / RussianRoulette};

	static constexpr int SamplesPerPixel{20000};
	static constexpr Float InverseSamplesPerPixel{1.0 / SamplesPerPixel};

	static constexpr bool SampleIndirectLight{true};

public:
	TArray<FVector> Framebuffer;

private:
	int _ResolutionX;
	int _ResolutionY;
};
