#include "Render.hpp"

#include "../logic/Logic.hpp"

#include "../shared/ResourcesMng.hpp"
#include "WorldRenderer.hpp"

#include <iostream>
#include <raylib.h>
#include <string>
#include <format>

#include "../shared/CameraMng.hpp"

void Render::Init(Logic* logic)
{
	this->logic = logic;

	ResourcesManager::RenderBlocksAtlas();
}

void Render::Update(double dt)
{
	World* world = logic->world; 

	ClearBackground({15, 12, 20});

	if (CameraMng::Camr())
	{
		GameCamera* cam = CameraMng::curCam;
		
		float blockSize = cam->WorldToScreenPoint();

		BeginMode2D(cam->Cam());
		render::RenderWorld(*world);
		render::RenderEntities(*world);
		for (int x = 0; x <= WORLD_CHUNKS_XY; x++)
		{
			DrawLine(x * WORLDCHUNK_XY, 0, x * WORLDCHUNK_XY, WORLD_CHUNKS_XY * WORLDCHUNK_XY, BLUE);
		}
		for (int y = 0; y <= WORLD_CHUNKS_XY; y++)
		{
			DrawLine(0, y * WORLDCHUNK_XY, WORLD_CHUNKS_XY * WORLDCHUNK_XY, y * WORLDCHUNK_XY, BLUE);
		}
		EndMode2D();

		Vector2 mousePos = cam->ScreenToWorld(GetMousePosition());
		Vector2I blockPos = {(int)mousePos.x, (int)mousePos.y};
		Vector2 blockScreen = cam->WorldToScreen({(float)blockPos.x, (float)blockPos.y});

		DrawRectangleLinesEx({blockScreen.x, blockScreen.y, blockSize, blockSize}, 1.0f, GREEN);

		auto bid = world->GetBlock(blockPos);
		auto blc = reg::GetBlock(bid);

		std::string blc_name = "?";

		if (blc)
		{
			blc_name = blc->name;
		}

		DrawText(blc_name.c_str(), blockScreen.x + blockSize + 5, blockScreen.y, 16, GREEN);
		DrawText(std::to_string(bid).c_str(), blockScreen.x + blockSize + 5, blockScreen.y+(15*1), 16, GREEN);
		DrawText(std::format("x: {}, y: {}", blockPos.x, blockPos.y).c_str(), blockScreen.x + blockSize + 5, blockScreen.y+(15*2), 16, GREEN);
		DrawText(std::format("cx: {}, cy: {}", blockPos.x/WORLDCHUNK_XY, blockPos.y/WORLDCHUNK_XY).c_str(), blockScreen.x + blockSize + 5, blockScreen.y+(15*3), 16, GREEN);
	}
	else 
	{
		std::cout << "ashibka stop 000 \n";
	}

	//overlay
	DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 20, GREEN);
	DrawText(std::to_string(GetTime()).c_str(), 10, 10 + 20, 20, GREEN);
}