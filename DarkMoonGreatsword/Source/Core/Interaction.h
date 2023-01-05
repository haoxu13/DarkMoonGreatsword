#pragma once

#include "CoreMinimal.h"

class FMaterial;
class FTriangleMesh;

class FInteraction
{
public:
	FVector Emit;
    FVector Coords;
    FVector TCoords; // UV coordinate, only using first two elements
    FVector Normal;
    float Distance{-1.f};
    FTriangleMesh* HitObject{nullptr};
    FMaterial* HitMaterial{nullptr};
	bool bHappened{false};
};
