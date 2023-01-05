#pragma once
#include "CoreMinimal.h"

class FRay
{
public:
	FRay() : MaxDistance(INFINITY), Time(0.0)
	{
	}

	FRay(const FVector& NewOrigin, const FVector& NewDirection, Float NewMaxDistance = INFINITY,
		Float NewTime = 0.0)
		: Origin(NewOrigin), Direction(NewDirection), MaxDistance(NewMaxDistance), Time(NewTime)
	{
	}

	FVector operator()(Float InDistance) const { return Origin + Direction * InDistance; }

public:
	FVector Origin;
	FVector Direction;
	Float MaxDistance;
	Float Time;
};
