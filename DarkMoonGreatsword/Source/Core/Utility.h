#pragma once

#include <filesystem>
#include <random>

// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define XSTR(s) STR(s)
#define STR(s) #s

#undef  PI
#define PI 					(3.1415926535897932384626433832795f)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

inline std::filesystem::path GetAssetPath(const std::string& AssetFile)
{
	const std::string TempFileName = "/" + AssetFile;
	return std::filesystem::path(XSTR(ASSET_DIR)) += std::filesystem::path(TempFileName);
}

inline constexpr float Epsilon = 0.000001f;

inline bool IsAlmostZero(float Number)
{
	return Number > -Epsilon && Number < Epsilon;
}

inline bool IsAlmostGreaterThanZero(float Number)
{
	return Number >= - Epsilon;
}

inline bool IsAlmostSmallerThanOne(float Number)
{
	constexpr float OnePlusEpsilon = 1.f + Epsilon;
	return Number <= OnePlusEpsilon;
}

inline bool IsAlmostInRange(float Number)
{
	return IsAlmostGreaterThanZero(Number) && IsAlmostSmallerThanOne(Number);
}

 // Distribution in range [0.0, 1.0]
inline float GetRandomFloat()
{
	std::random_device RandomDevice;
	std::mt19937 Rng(RandomDevice());
	const std::uniform_real_distribution<float> Dist(0.f, 1.f);

	return Dist(Rng);
}

inline int GetRandomIntInRange(int Min, int Max)
{
	std::random_device RandomDevice;
	std::mt19937 Rng(RandomDevice());
	const std::uniform_int_distribution Dist(Min, Max);

	return Dist(Rng);
}
