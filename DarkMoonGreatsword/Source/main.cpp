#include <chrono>
#include <iostream>

#include "stdio.h"
#include "Core/Integrator.h"
#include "Core/AreaLight.h"
#include "Core/Material.h"
#include "Core/Scene.h"
#include "Core/TriangleMesh.h"
#include "Core/Utility.h"

static constexpr bool bReadFrameBufferFromFile = false;

int main()
{
	constexpr int ResolutionX = 784;
	constexpr int ResolutionY = 784;

	if constexpr (bReadFrameBufferFromFile)
	{
		TArray<FVector> NewFramebuffer(ResolutionX * ResolutionY);
		ImportFrameBufferFromTextFile(NewFramebuffer, ResolutionX, ResolutionY);
		ExportFrameBufferToPpm(NewFramebuffer, ResolutionX, ResolutionY);
		return 0;
	}

	FScene Scene(ResolutionX, ResolutionY);

	FMaterial* Red = new FMaterial("Red");
	Red->Kd = FVector(0.63, 0.065, 0.05);
	FMaterial* Green = new FMaterial("Green");
	Green->Kd = FVector(0.14, 0.45, 0.091);
	FMaterial* White = new FMaterial("White");
	White->Kd = FVector(0.725, 0.71, 0.68);
	FMaterial* LightMaterial = new FMaterial("Light");
	LightMaterial->Emission = 8.0 * FVector(0.747 + 0.058, 0.747 + 0.285, 0.747) + 15.6 *
		FVector(0.740 + 0.287, 0.740 + 0.160, 0.740) + 18.4 * FVector(0.737 + 0.642, 0.737 + 0.159, 0.737);
	LightMaterial->Kd = FVector(0.65);

	// https://www.graphics.cornell.edu/online/box/data.html
	FTriangleMesh Floor("Models/cornellbox/floor.obj", White);
	FTriangleMesh Shortbox("Models/cornellbox/shortbox.obj", White);
	FTriangleMesh Tallbox("Models/cornellbox/tallbox.obj", White);
	FTriangleMesh Left("Models/cornellbox/left.obj", Red);
	FTriangleMesh Right("Models/cornellbox/right.obj", Green);
	FAreaLight Light("Models/cornellbox/light.obj", LightMaterial);

	Scene.Add(&Floor);
	Scene.Add(&Shortbox);
	Scene.Add(&Tallbox);
	Scene.Add(&Left);
	Scene.Add(&Right);
	Scene.AddLight(&Light);

	FPathIntegrator PathIntegrator;

	const auto Start = std::chrono::system_clock::now();
	PathIntegrator.Render(Scene);
	const auto Stop = std::chrono::system_clock::now();

	ExportFrameBufferToBinaryFile(PathIntegrator.Framebuffer, ResolutionX, ResolutionY);
	ExportFrameBufferToPpm(PathIntegrator.Framebuffer, ResolutionX, ResolutionY);

	std::cout << "\nRender complete: \n";
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(Stop - Start).count() << " hours\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(Stop - Start).count() <<
		" minutes\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(Stop - Start).count() <<
		" seconds\n";

	return 0;
}
