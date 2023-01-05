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
	static constexpr int SamplesPerPixel{5000};
	static constexpr bool SampleIndirectLight{true};

private:
	TArray<FVector> _Framebuffer;
	int _ResolutionX;
	int _ResolutionY;

	void SaveToFile();
};
