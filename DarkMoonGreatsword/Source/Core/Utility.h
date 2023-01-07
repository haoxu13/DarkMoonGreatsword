#pragma once

#include "CoreMinimal.h"
#include "ToneMappingUtility.h"

#include <filesystem>
#include <fstream>
#include <sstream>

// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define XSTR(s) STR(s)
#define STR(s) #s

inline std::filesystem::path GetAssetPath(const std::string& AssetFile)
{
	const std::string TempFileName = "/" + AssetFile;
	return std::filesystem::path(XSTR(ASSET_DIR)) += std::filesystem::path(TempFileName);
}

inline void ExportFrameBufferToPpm(const TArray<FVector>& InFramebuffer, int InResolutionX, int InResolutionY)
{
	FILE* Fp = fopen("../Result/result.ppm", "wb");
	(void)fprintf(Fp, "P6\n%d %d\n255\n", InResolutionX, InResolutionY);

	Float MaxLuminance = -INFINITY;
	for (const auto& Pixel : InFramebuffer)
	{
		const Float Luminance = luminance(Pixel);
		if (Luminance > MaxLuminance)
		{
			MaxLuminance = Luminance;
		}
	}

	for (const auto& Pixel : InFramebuffer)
	{
		static unsigned char Color[3];
		constexpr Float Gamma = 1.0 / 2.2;
		const FVector ToneMappedColor = reinhard_extended_luminance(Pixel, MaxLuminance);
		Color[0] = static_cast<unsigned char>(255 * std::pow(ToneMappedColor.X, Gamma));
		Color[1] = static_cast<unsigned char>(255 * std::pow(ToneMappedColor.Y, Gamma));
		Color[2] = static_cast<unsigned char>(255 * std::pow(ToneMappedColor.Z, Gamma));
		fwrite(Color, 1, 3, Fp);
	}

	fclose(Fp);
}

inline void ExportFrameBufferToBinaryFile(const TArray<FVector>& InFramebuffer, int InResolutionX, int InResolutionY)
{
	std::ostringstream FileNameStream;
	FileNameStream << "../Result/FrameBufferValue_" << InResolutionX << "_" << InResolutionY;
	const std::string FileName = FileNameStream.str();
	std::ofstream FrameBufferTextFileStream(FileName, std::ios::out | std::ios::binary);
	// size_t FrameBufferSize = InFramebuffer.size();
	// FrameBufferTextFileStream.write((char*)&FrameBufferSize, sizeof FrameBufferSize);
	FrameBufferTextFileStream.write((char*)InFramebuffer.data(), InFramebuffer.size() * sizeof(FVector));
	FrameBufferTextFileStream.close();
}

inline void ImportFrameBufferFromTextFile(const TArray<FVector>& InFramebuffer, int InResolutionX, int InResolutionY)
{
	std::ostringstream FileNameStream;
	FileNameStream << "../Result/FrameBufferValue_" << InResolutionX << "_" << InResolutionY;
	const std::string FileName = FileNameStream.str();
	std::ifstream FrameBufferTextFileStream(FileName, std::ios::in | std::ios::binary);

	// Get length of file
	FrameBufferTextFileStream.seekg(0, std::ios::end);
	size_t FileLength = FrameBufferTextFileStream.tellg();

	// Read file
	FrameBufferTextFileStream.seekg(0, std::ios::beg);
	FrameBufferTextFileStream.read((char*)InFramebuffer.data(), FileLength);

	FrameBufferTextFileStream.close();
}
