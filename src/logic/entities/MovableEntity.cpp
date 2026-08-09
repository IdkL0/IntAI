#include "MovableEntity.hpp"

#include "raylib.h"
#include "raymath.h"

#include "../../shared/AABBHelper.hpp"
#include <algorithm>

#include <cstdint>

#include "../World.hpp"
#include "../../shared/BlocksRegistry.hpp"

void MovableEntity::Tick(double dt)
{
	if (autoMove)
	{
		Move(vel * dt);
		vel.x *= velDrag;
		if (useGravity)
		{
			vel += world->gravity*dt;
		}
	}
}

void MovableEntity::Move(Vector2 m)
{
	if (m.x == 0 && m.y == 0) return;

	Vector2 next = pos + m;

	if (collide)
	{
		int bMinX = (int)std::floor(pos.x + box.x) - 1;
		int bMinY = (int)std::floor(pos.y + box.y) - 1;
		int bMaxX = (int)std::ceil(pos.x + box.x + box.width) + 1;
		int bMaxY = (int)std::ceil(pos.y + box.y + box.height) + 1;

		bMinX = std::clamp(bMinX, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
		bMinY = std::clamp(bMinY, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
		bMaxX = std::clamp(bMaxX, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);
		bMaxY = std::clamp(bMaxY, 0, WORLD_CHUNKS_XY*WORLDCHUNK_XY);

		Rectangle worldBox = {next.x + box.x, next.y + box.y, box.width, box.height};

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

						if (aabb::Box(worldBox, blockWorld)) 
						{
							float centerX = worldBox.x + worldBox.width / 2.0f;
							float centerY = worldBox.y + worldBox.height / 2.0f;
							float otherCenterX = blockWorld.x + blockWorld.width / 2.0f;
							float otherCenterY = blockWorld.y + blockWorld.height / 2.0f;

							float overlapX = (worldBox.width + blockWorld.width) / 2.0f - std::abs(centerX - otherCenterX);
							float overlapY = (worldBox.height + blockWorld.height) / 2.0f - std::abs(centerY - otherCenterY);

							if (overlapX < overlapY)
							{
								if (centerX < otherCenterX)
								{
									next.x = blockWorld.x - box.x - box.width;
								}
								else
								{
									next.x = blockWorld.x + blockWorld.width - box.x;
								}
								worldBox.x = next.x + box.x;
								vel.x = 0;
							}
							else
							{
								if (centerY < otherCenterY)
								{
									next.y = blockWorld.y - box.y - box.height;
								}
								else
								{
									next.y = blockWorld.y + blockWorld.height - box.y;
								}
								worldBox.y = next.y + box.y;
								vel.y = 0;
							}
						}
					}
				}
			}
		}
	}

	pos = next;
}
