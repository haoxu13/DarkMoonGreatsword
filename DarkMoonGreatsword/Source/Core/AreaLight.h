#pragma once
#include "TriangleMesh.h"

class FAreaLight : public FTriangleMesh
{
public:
	explicit FAreaLight(const FString& InFilename, FMaterial* InMaterial = new FMaterial());

	void SampleLight(FInteraction& OutSampleInteraction, float& OutPdf) const;

protected:
	FInteraction InteractionInfo;
	float InverseArea{0.f};
};
