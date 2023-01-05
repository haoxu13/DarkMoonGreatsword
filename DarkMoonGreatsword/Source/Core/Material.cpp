#include "Material.h"

FVector ToWorld(const FVector& LocalVector, const FVector& Normal)
{
	FVector B, C;
	if (std::fabs(Normal.X) > std::fabs(Normal.Y))
	{
		const Float InverseLength = 1.0 / std::sqrt(Normal.X * Normal.X + Normal.Z * Normal.Z);
		C = FVector(Normal.Z * InverseLength, 0.0, -Normal.X * InverseLength);
	}
	else
	{
		const Float InverseLength = 1.0 / std::sqrt(Normal.Y * Normal.Y + Normal.Z * Normal.Z);
		C = FVector(0.0, Normal.Z * InverseLength, -Normal.Y * InverseLength);
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
	const Float X1 = GetRandomFloat();
	const Float X2 = GetRandomFloat();
	const Float Z = std::fabs(1.0 - 2.0 * X1);
	const Float R = std::sqrt(1.0 - Z * Z);
	const Float Phi = 2 * PI * X2;
	const FVector LocalRay(R * std::cos(Phi), R * std::sin(Phi), Z);
	return ToWorld(LocalRay, InNormal);
}

FVector FMaterial::Eval(const FVector& InRayDirection, const FVector& InViewDirection, const FVector& InNormal)
{
	// calculate the contribution of diffuse   model
	const Float CosTheta = DotProduct(InNormal, InRayDirection);
	if (CosTheta > 0.0)
	{
		const FVector Diffuse = Kd / PI;
		return Diffuse;
	}

	return FVector();
}

Float FMaterial::Pdf(const FVector& InRayDirection, const FVector& OutRayDirection, const FVector& N)
{
	if (DotProduct(OutRayDirection, N) > 0.0)
	{
		return 0.5 / PI;
	}

	return 0.0;
}
