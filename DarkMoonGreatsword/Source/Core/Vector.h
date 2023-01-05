#pragma once
#include "Utility.h"

struct FVector
{
public:
	Float X{0.0};
	Float Y{0.0};
	Float Z{0.0};

public:
	FVector();
	FVector(Float _X, Float _Y, Float _Z);
	explicit FVector(Float _X);

	FVector operator*(const FVector& Other) const;

	FVector operator+(const FVector& Other) const;
	FVector operator-(const FVector& Other) const;
	FVector operator-() const;

	FVector operator/(Float Number) const;

	FVector& operator+=(const FVector& Other);

	static bool IsAlmostSame(const FVector& VectorA, const FVector& VectorB);

	// Inner product
	Float ScalarProduct(const FVector& Other) const;
	Float DotProduct(const FVector& Other) const;
	FVector CrossProduct(const FVector& Other) const;

	Float Norm() const;

	FVector Normalize() const;

	// Angle in radian
	Float Angle(const FVector& Other) const;

public:
	Float operator[](int I) const
	{
		if (I == 0) return X;
		if (I == 1) return Y;
		return Z;
	}

	Float& operator[](int I)
	{
		if (I == 0) return X;
		if (I == 1) return Y;
		return Z;
	}
};

FVector operator*(Float Lhs, const FVector& Rhs);
FVector operator*(const FVector& Lhs, Float Rhs);

FVector Normalize(const FVector& InVector);
Float DotProduct(const FVector& InVector1, const FVector& InVector2);
