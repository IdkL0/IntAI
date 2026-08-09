#include "PlayerEntityController.hpp"

#include <cmath>
#include <raylib.h>

#include "../../shared/CameraMng.hpp"

#include "../entities/AIEntity.hpp"

#include "../../shared/RngEngine.hpp"

void PlayerEntityController::Start()
{

}

void PlayerEntityController::Update(double dt)
{
	if (!CameraMng::Camr()) return;

	Vector2 mousePos = CameraMng::curCam->ScreenToWorld(GetMousePosition());

	if (IsKeyDown(KEY_LEFT_ALT))
	{
		mousePos.x = std::floor(mousePos.x) + .5f;
		mousePos.y = std::floor(mousePos.y) + .5f;
	}
	
	if (IsKeyPressed(KEY_Q))
	{
		auto ent = std::make_unique<MovableEntity>(world);
		ent->pos = mousePos;
		//ent->vel = {rng::RandFloat(-10, 10), rng::RandFloat(-10, 10)};
		//ent->velDrag = 1;

		world.entities.push_back(std::move(ent));
	}
	else if (IsKeyPressed(KEY_W))
	{
		auto ent = std::make_unique<AIEntity>(world);
		ent->pos = mousePos;
		//ent->vel = {rng::RandFloat(-10, 10), rng::RandFloat(-10, 10)};
		ent->velDrag = 1;

		world.entities.push_back(std::move(ent));
	}
}