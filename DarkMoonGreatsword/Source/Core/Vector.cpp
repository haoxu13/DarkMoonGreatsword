#include "Vector.h"

#include <cmath>

FVector operator*(float Lhs, const FVector& Rhs)
{
	FVector ResultVector;
	ResultVector.X = Rhs.X * Lhs;
	ResultVector.Y = Rhs.Y * Lhs;
	ResultVector.Z = Rhs.Z * Lhs;

	return ResultVector;
}

FVector operator*(const FVector& Lhs, float Rhs)
{
	FVector ResultVector;
	ResultVector.X = Rhs * Lhs.X;
	ResultVector.Y = Rhs * Lhs.Y;
	ResultVector.Z = Rhs * Lhs.Z;

	return ResultVector;
}

FVector Normalize(const FVector& InVector)
{
	return InVector.Normalize();
}

float DotProduct(const FVector& InVector1, const FVector& InVector2)
{
	return InVector1.DotProduct(InVector2);
}

FVector::FVector():
	X(0.f),
	Y(0.f),
	Z(0.f)
{
}

FVector::FVector(float _X, float _Y, float _Z):
	X(_X),
	Y(_Y),
	Z(_Z)
{
}

FVector::FVector(float _X):
	X(_X),
	Y(_X),
	Z(_X)
{
}

FVector FVector::operator*(const FVector& Other) const
{
	FVector ResultVector;

	const float& X2 = Other.X;
	const float& Y2 = Other.Y;
	const float& Z2 = Other.Z;

	ResultVector.X = X * X2;
	ResultVector.Y = Y * Y2;
	ResultVector.Z = Z * Z2;

	return ResultVector;
}

FVector FVector::operator+(const FVector& Other) const
{
	FVector ResultVector;

	const float& X2 = Other.X;
	const float& Y2 = Other.Y;
	const float& Z2 = Other.Z;

	ResultVector.X = X + X2;
	ResultVector.Y = Y + Y2;
	ResultVector.Z = Z + Z2;

	return ResultVector;
}

FVector FVector::operator-(const FVector& Other) const
{
	FVector ResultVector;

	ResultVector.X = X - Other.X;
	ResultVector.Y = Y - Other.Y;
	ResultVector.Z = Z - Other.Z;

	return ResultVector;
}

FVector FVector::operator-() const
{
	FVector ResultVector;

	ResultVector.X = -X;
	ResultVector.Y = -Y;
	ResultVector.Z = -Z;

	return ResultVector;
}

FVector FVector::operator/(float Number) const
{
	FVector ResultVector;

	ResultVector.X = X / Number;
	ResultVector.Y = Y / Number;
	ResultVector.Z = Z / Number;

	return ResultVector;
}

FVector& FVector::operator+=(const FVector& Other)
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;

	return *this;
}

float FVector::ScalarProduct(const FVector& Other) const
{
	return X * Other.X + Y * Other.Y + Z * Other.Z;
}

float FVector::DotProduct(const FVector& Other) const
{
	return ScalarProduct(Other);
}

FVector FVector::CrossProduct(const FVector& Other) const
{
	FVector ResultVector;

	ResultVector.X = Y * Other.Z - Z * Other.Y;
	ResultVector.Y = Z * Other.X - X * Other.Z;
	ResultVector.Z = X * Other.Y - Y * Other.X;

	return ResultVector;
}

float FVector::Norm() const
{
	return sqrt(ScalarProduct(*this));
}

FVector FVector::Normalize() const
{
	FVector ResultVector;

	const float Length = Norm();

	ResultVector.X = X / Length;
	ResultVector.Y = Y / Length;
	ResultVector.Z = Z / Length;

	return ResultVector;
}

float FVector::Angle(const FVector& Other) const
{
	const float InverseNorm1 = 1.f / Norm();
	const float InverseNorm2 = 1.f / Other.Norm();
	const float CosTheta = ScalarProduct(Other) * InverseNorm1 * InverseNorm2;
	return acos(CosTheta);
}
