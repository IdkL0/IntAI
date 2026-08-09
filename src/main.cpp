#include <raylib.h>
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

		EndDrawing();
	}
	res::Unload();

	CloseWindow();

	CameraMng::DESTROY();

	return 0;
}
