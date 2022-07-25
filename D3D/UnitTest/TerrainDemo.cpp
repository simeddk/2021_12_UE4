#include "stdafx.h"
#include "TerrainDemo.h"

void TerrainDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(13, 0, 0);
	Context::Get()->GetCamera()->Position(100, 95, -130);
	dynamic_cast<Freedom*>(Context::Get()->GetCamera())->Speed(50, 2);

	shader = new Shader(L"07_Terrain.fxo");

	terrain = new Terrain(shader, L"HeightMap256.png");
}

void TerrainDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void TerrainDemo::Update()
{
	static UINT Pass = shader->PassCount() - 1;
	ImGui::InputInt("Pass", (int*)&Pass);
	Pass %= shader->PassCount();
	terrain->Pass() = Pass;

	terrain->Update();
}

void TerrainDemo::Render()
{
	terrain->Render();
}
