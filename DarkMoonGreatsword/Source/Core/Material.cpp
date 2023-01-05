#include "Material.h"

FVector ToWorld(const FVector& LocalVector, const FVector& Normal)
{
	FVector B, C;
	if (std::fabs(Normal.X) > std::fabs(Normal.Y))
	{
		const float InverseLength = 1.0f / std::sqrt(Normal.X * Normal.X + Normal.Z * Normal.Z);
		C = FVector(Normal.Z * InverseLength, 0.0f, -Normal.X * InverseLength);
	}
	else
	{
		const float InverseLength = 1.0f / std::sqrt(Normal.Y * Normal.Y + Normal.Z * Normal.Z);
		C = FVector(0.0f, Normal.Z * InverseLength, -Normal.Y * InverseLength);
	}
	B = C.CrossProduct(Normal);
	return LocalVector.X * B + LocalVector.Y * C + LocalVector.Z * Normal;
}

FMaterial::FMaterial(const FString& NewName):
	Name(NewName)
{
}

FVector FMaterial::Sample(const FVector& InRayDirection, const FVector& InNormal)
{
	const float X1 = GetRandomFloat();
	const float X2 = GetRandomFloat();
	const float Z = std::fabs(1.0f - 2.0f * X1);
	const float R = std::sqrt(1.0f - Z * Z);
	const float Phi = 2 * PI * X2;
	const FVector LocalRay(R * std::cos(Phi), R * std::sin(Phi), Z);
	return ToWorld(LocalRay, InNormal);
}

FVector FMaterial::Eval(const FVector& InRayDirection, const FVector& InViewDirection, const FVector& InNormal)
{
	// calculate the contribution of diffuse   model
	const float CosTheta = DotProduct(InNormal, InRayDirection);
	if (CosTheta > 0.0f)
	{
		const FVector Diffuse = Kd / PI;
		return Diffuse;
	}

	return FVector();
}

float FMaterial::Pdf(const FVector& InRayDirection, const FVector& OutRayDirection, const FVector& N)
{
	if (DotProduct(OutRayDirection, N) > 0.0f)
	{
		return 0.5f / PI;
	}

	return 0.0f;
}
