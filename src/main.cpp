#include <iostream>
#include <raylib.h>

#include "imgui.h"
#include "rlImGui.h"

#include <string>

#include "logic/Logic.hpp"
#include "render/Render.hpp"
#include "shared/ResourcesMng.hpp"
#include "shared/CameraMng.hpp"
#include "shared/ResourcesMng.hpp"

int main(int argc, char* argv[])
{
	SetExitKey(0);

	//SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(800, 600, "IntAI");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(0);
	rlImGuiSetup(true);

	res::Load();

	CameraMng::SetupCamera();

	Logic logic;
	Render render;

	logic.Init();

	render.Init(&logic);

	double last = GetTime();

	while (!WindowShouldClose())
	{
		CameraMng::UpdCam();
		
		double now = GetTime();
		double delta = now - last;
		last = now;

		logic.Update(delta);

		BeginDrawing();

		render.Update(delta);

		rlImGuiBegin();

		// ImGui::Begin("Test");

		// ImGui::Text("Poka mir!");

		// ImGui::End();

		rlImGuiEnd();

		EndDrawing();
	}
	res::Unload();

	rlImGuiShutdown();
	CloseWindow();

	CameraMng::DESTROY();

	return 0;
}
