#pragma once
#include "CoreMinimal.h"

class FRay
{
public:
	FRay() : MaxDistance(INFINITY), Time(0.f)
	{
	}

	FRay(const FVector& NewOrigin, const FVector& NewDirection, float NewMaxDistance = INFINITY,
		float NewTime = 0.f)
		: Origin(NewOrigin), Direction(NewDirection), MaxDistance(NewMaxDistance), Time(NewTime)
	{
	}

	FVector operator()(float InDistance) const { return Origin + Direction * InDistance; }

public:
	FVector Origin;
	FVector Direction;
	float MaxDistance;
	float Time;
};
