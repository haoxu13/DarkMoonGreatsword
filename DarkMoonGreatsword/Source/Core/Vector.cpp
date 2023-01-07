#include "Vector.h"

#include <cmath>

#include "Utility.h"

FVector operator+(Float Lhs, const FVector& Rhs)
{
	return Rhs + Lhs;
}

FVector operator*(Float Lhs, const FVector& Rhs)
{
	FVector ResultVector;
	ResultVector.X = Rhs.X * Lhs;
	ResultVector.Y = Rhs.Y * Lhs;
	ResultVector.Z = Rhs.Z * Lhs;

	return ResultVector;
}

FVector operator*(const FVector& Lhs, Float Rhs)
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

Float DotProduct(const FVector& InVector1, const FVector& InVector2)
{
	return InVector1.DotProduct(InVector2);
}

FVector::FVector():
	X(0.0),
	Y(0.0),
	Z(0.0)
{
}

FVector::FVector(Float _X, Float _Y, Float _Z):
	X(_X),
	Y(_Y),
	Z(_Z)
{
}

FVector::FVector(Float _X):
	X(_X),
	Y(_X),
	Z(_X)
{
}

FVector FVector::operator*(const FVector& Other) const
{
	FVector ResultVector;

	const Float& X2 = Other.X;
	const Float& Y2 = Other.Y;
	const Float& Z2 = Other.Z;

	ResultVector.X = X * X2;
	ResultVector.Y = Y * Y2;
	ResultVector.Z = Z * Z2;

	return ResultVector;
}

FVector FVector::operator+(const FVector& Other) const
{
	FVector ResultVector;

	const Float& X2 = Other.X;
	const Float& Y2 = Other.Y;
	const Float& Z2 = Other.Z;

	ResultVector.X = X + X2;
	ResultVector.Y = Y + Y2;
	ResultVector.Z = Z + Z2;

	return ResultVector;
}

FVector FVector::operator+(Float ScalarValue) const
{
	FVector ResultVector;

	ResultVector.X = X + ScalarValue;
	ResultVector.Y = Y + ScalarValue;
	ResultVector.Z = Z + ScalarValue;

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

FVector FVector::operator/(const FVector& Other) const
{
	FVector ResultVector;

	ResultVector.X = X / Other.X;
	ResultVector.Y = Y / Other.Y;
	ResultVector.Z = Z / Other.Z;

	return ResultVector;
}

FVector FVector::operator/(Float Number) const
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

bool FVector::IsAlmostSame(const FVector& VectorA, const FVector& VectorB)
{
	return IsAlmostSameFloat(VectorA.X, VectorB.X, Epsilon) && IsAlmostSameFloat(VectorA.Y, VectorB.Y, Epsilon) && IsAlmostSameFloat(VectorA.Z, VectorB.Z, Epsilon);
}

Float FVector::ScalarProduct(const FVector& Other) const
{
	return X * Other.X + Y * Other.Y + Z * Other.Z;
}

Float FVector::DotProduct(const FVector& Other) const
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

Float FVector::Norm() const
{
	return sqrt(ScalarProduct(*this));
}

FVector FVector::Normalize() const
{
	FVector ResultVector;

	const Float Length = Norm();

	ResultVector.X = X / Length;
	ResultVector.Y = Y / Length;
	ResultVector.Z = Z / Length;

	return ResultVector;
}

Float FVector::Angle(const FVector& Other) const
{
	const Float InverseNorm1 = 1.0 / Norm();
	const Float InverseNorm2 = 1.0 / Other.Norm();
	const Float CosTheta = ScalarProduct(Other) * InverseNorm1 * InverseNorm2;
	return acos(CosTheta);
}
