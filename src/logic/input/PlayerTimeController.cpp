#include "PlayerTimeController.hpp"

#include <cmath>
#include <raylib.h>

void PlayerTimeController::Start()
{
	before_stop = -1.f;
}

void PlayerTimeController::Update(double dt)
{
	if (IsKeyPressed(KEY_B)) world.timeScale = spedScale;
	else if (IsKeyPressed(KEY_N)) world.timeScale = slowScale;
	else if (IsKeyPressed(KEY_M)) world.timeScale = defScale;
	else if (IsKeyPressed(KEY_SPACE))
	{
		if (before_stop <= 0)
		{
			before_stop = world.timeScale;
			world.timeScale = stopScale;
		}
		else
		{
			world.timeScale = before_stop;
			before_stop = -1.f;
		}
	}
}