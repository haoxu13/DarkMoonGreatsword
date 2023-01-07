#pragma once
#include "CoreMinimal.h"

// Ref: 
// https://64.github.io/tonemapping
// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/

inline FVector ACESFilm(const FVector& x)
{
	Float a = 2.51;
	Float b = 0.03;
	Float c = 2.43;
	Float d = 0.59;
	Float e = 0.14;
	return Saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}

inline FVector Reinhard(const FVector& v)
{
	return v / (1.0 + v);
}

inline Float luminance(FVector v)
{
	return DotProduct(v, FVector(0.2126, 0.7152, 0.0722));
}

inline FVector change_luminance(FVector c_in, Float l_out)
{
	Float l_in = luminance(c_in);
	if (IsAlmostZero(l_in))
	{
		return c_in;
	}

	return c_in * (l_out / l_in);
}

inline FVector reinhard_extended_luminance(FVector v, Float max_white_l)
{
    Float l_old = luminance(v);
    Float numerator = l_old * (1.0 + (l_old / (max_white_l * max_white_l)));
    Float l_new = numerator / (1.0 + l_old);
    return Saturate(change_luminance(v, l_new));
}