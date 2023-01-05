#pragma once

struct FVector
{
public:
	float X{0.f};
	float Y{0.f};
	float Z{0.f};

public:
	FVector();
	FVector(float _X, float _Y, float _Z);
	explicit FVector(float _X);

	FVector operator*(const FVector& Other) const;

	FVector operator+(const FVector& Other) const;
	FVector operator-(const FVector& Other) const;
	FVector operator-() const;

	FVector operator/(float Number) const;

	FVector& operator+=(const FVector& Other);

	// Inner product
	float ScalarProduct(const FVector& Other) const;
	float DotProduct(const FVector& Other) const;
	FVector CrossProduct(const FVector& Other) const;

	float Norm() const;

	FVector Normalize() const;

	// Angle in radian
	float Angle(const FVector& Other) const;

public:
	float operator[](int I) const
	{
		if (I == 0) return X;
		if (I == 1) return Y;
		return Z;
	}

	float& operator[](int I)
	{
		if (I == 0) return X;
		if (I == 1) return Y;
		return Z;
	}
};

FVector operator*(float Lhs, const FVector& Rhs);
FVector operator*(const FVector& Lhs, float Rhs);

FVector Normalize(const FVector& InVector);
float DotProduct(const FVector& InVector1, const FVector& InVector2);
