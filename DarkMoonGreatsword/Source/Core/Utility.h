#pragma once

#include <filesystem>
#include <random>

// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define XSTR(s) STR(s)
#define STR(s) #s

#undef  PI
#define PI 					(3.1415926535897932384626433832795)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef double Float;

inline std::filesystem::path GetAssetPath(const std::string& AssetFile)
{
	const std::string TempFileName = "/" + AssetFile;
	return std::filesystem::path(XSTR(ASSET_DIR)) += std::filesystem::path(TempFileName);
}

inline constexpr Float Epsilon = 0.000001;

inline bool IsAlmostSameFloat(Float Number1, Float Number2, Float Error = Epsilon)
{
	return std::fabs(Number1 - Number2) < Error;
}

inline bool IsAlmostZero(Float Number)
{
	return Number > -Epsilon && Number < Epsilon;
}

inline bool IsAlmostGreaterThanZero(Float Number)
{
	return Number >= - Epsilon;
}

inline bool IsAlmostSmallerThanOne(Float Number)
{
	constexpr Float OnePlusEpsilon = 1.0 + Epsilon;
	return Number <= OnePlusEpsilon;
}

inline bool IsAlmostInRange(Float Number)
{
	return IsAlmostGreaterThanZero(Number) && IsAlmostSmallerThanOne(Number);
}

// Distribution in range [0.0, 1.0]
inline Float GetRandomFloat(Float Min = 0.0, Float Max = 1.0)
{
	std::random_device RandomDevice;
	std::mt19937 Rng(RandomDevice());
	const std::uniform_real_distribution<Float> Dist(Min, Max);

	return Dist(Rng);
}

inline int GetRandomIntInRange(int Min, int Max)
{
	std::random_device RandomDevice;
	std::mt19937 Rng(RandomDevice());
	const std::uniform_int_distribution Dist(Min, Max);

	return Dist(Rng);
}
