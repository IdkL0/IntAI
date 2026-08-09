#include "AIEntity.hpp"

#include "../../shared/RngEngine.hpp"

#include "raylib.h"
#include "raymath.h"

#include "../../shared/AABBHelper.hpp"
#include <algorithm>

#include <cstdint>

#include "../World.hpp"
#include "../../shared/BlocksRegistry.hpp"

void AIEntity::Tick(double dt)
{
	MovableEntity::Tick(dt);

	bool isGrounded = CheckGrounded();

	if (isGrounded)
	{
		if (rng::RandBool(0.3f))
		{
			vel.y = -12;
			return;
		}

		if (rng::RandBool())
		{
			vel.x = 5;
		}
		else 
		{
			vel.x = -5;
		}
	}
}

bool AIEntity::CheckGrounded()
{
	int bMinX = (int)std::floor(pos.x + box.x);
	int bMinY = (int)std::floor(pos.y + box.y);
	int bMaxX = (int)std::ceil(pos.x + box.x + box.width);
	int bMaxY = (int)std::ceil(pos.y + box.y + box.height) + 1;

	bMinX = std::clamp(bMinX, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
	bMinY = std::clamp(bMinY, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
	bMaxX = std::clamp(bMaxX, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
	bMaxY = std::clamp(bMaxY, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);

	for (int x = bMinX; x < bMaxX+1; x++)
	{
		for (int y = bMinY; y < bMaxY+1; y++)
		{
			uint16_t b = world->GetBlock(x, y);

			auto blc = reg::GetBlock(b);

			if (blc)
			{
				if (blc->solid)
				{
					Rectangle blockWorld = blc->hitbox;
					blockWorld = {(float)x + blockWorld.x, (float)y + blockWorld.y, blockWorld.width, blockWorld.height};

					Vector2 v1 = {0, box.y + box.height + 0.1f};
					v1 += pos;

					Vector2 in;
					float f;

					if (aabb::Line(blockWorld, pos, v1, in, f))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}