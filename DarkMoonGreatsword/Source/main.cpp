#include <chrono>
#include <iostream>

#include "stdio.h"
#include "Core/Integrator.h"
#include "Core/AreaLight.h"
#include "Core/Material.h"
#include "Core/Scene.h"
#include "Core/TriangleMesh.h"
#include "Core/Utility.h"

int main()
{
	FScene Scene(784, 784);

	FMaterial* Red = new FMaterial("Red");
	Red->Kd = FVector(0.63f, 0.065f, 0.05f);
	FMaterial* Green = new FMaterial("Green");
	Green->Kd = FVector(0.14f, 0.45f, 0.091f);
	FMaterial* White = new FMaterial("White");
	White->Kd = FVector(0.725f, 0.71f, 0.68f);
	FMaterial* LightMaterial = new FMaterial("Light");
	LightMaterial->Emission = 8.0f * FVector(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) + 15.6f *
		FVector(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) + 18.4f * FVector(0.737f + 0.642f, 0.737f + 0.159f, 0.737f);
	LightMaterial->Kd = FVector(0.65f);

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

	std::cout << "\nRender complete: \n";
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(Stop - Start).count() << " hours\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(Stop - Start).count() <<
		" minutes\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(Stop - Start).count() <<
		" seconds\n";

	return 0;
}
