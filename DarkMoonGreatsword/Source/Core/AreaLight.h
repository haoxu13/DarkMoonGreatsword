#pragma once
#include "TriangleMesh.h"

class FAreaLight : public FTriangleMesh
{
public:
	explicit FAreaLight(const FString& InFilename, FMaterial* InMaterial = new FMaterial());

	void SampleLight(FInteraction& OutSampleInteraction, Float& OutPdf) const;

	Float Area{0.0};

protected:
	FInteraction InteractionInfo;
	Float InverseArea{0.0};
};
