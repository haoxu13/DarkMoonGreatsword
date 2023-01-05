#pragma once

#include "CoreMinimal.h"

class FMaterial;
class FTriangle;

class FInteraction
{
public:
	FVector Emit;
    FVector Coords;
    FVector TCoords; // UV coordinate, only using first two elements
    FVector Normal;
    Float Distance{-1.0};
    FTriangle* HitTriangle{nullptr};
    FMaterial* HitMaterial{nullptr};
	bool bHappened{false};
};
