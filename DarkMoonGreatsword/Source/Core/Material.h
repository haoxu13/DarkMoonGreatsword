#pragma once
#include "CoreMinimal.h"

class FMaterial
{
public:
	explicit FMaterial(const FString& NewName = "");

    // sample a ray by Material properties
    FVector Sample(const FVector& InRayDirection, const FVector &InNormal);
    // given a ray, calculate the contribution of this ray
    FVector Eval(const FVector &InRayDirection, const FVector &InViewDirection, const FVector &InNormal);
    // given a ray, calculate the PdF of this ray
    float Pdf(const FVector &InRayDirection, const FVector &OutRayDirection, const FVector &N);

public:
	// Diffuse, Specular
	FVector Kd, Ks;
	FVector Emission;

protected:
	FString Name;
};
