#include "AIEntity.hpp"

#include "../../shared/RngEngine.hpp"
#include "../../shared/IntAIHelper.hpp"

#include "raylib.h"
#include "raymath.h"

#include "../../shared/AABBHelper.hpp"
#include <algorithm>

#include <climits>
#include <cstdint>

#include "../World.hpp"

AIEntity::AIEntity(World &world) : MovableEntity(world)
{
	brain = rng::RandInt<uint64_t>(0, ULONG_LONG_MAX);
}

void AIEntity::Tick(double dt)
{
	MovableEntity::Tick(dt);

	bool isGrounded = CheckGrounded();

	if (isGrounded)
	{
		velDrag = 0.8f;

		if (curState != AIState::Idle)
		{
			float jumpchance = 0.5f;
			if (curState == HappyJumping) rng::RandFloat(0.6, 0.8);
			if (aii::RandBoolMut(0.5, brain))
			{
				if (aii::RandBoolMut(0.8, brain))
				{
					float movDir = 0.f;
					switch (curState) {
						case Idle:
							break;
						case JustJumpwalkin:
							movDir = rng::RandFloat<float>(0.6f, 1.f);
							break;
						case HappyJumping:
							movDir = rng::RandFloat<float>(0.1f, 0.4f);
							break;
						case WannaSuicide:
						case GoToTarget:
							break;
					}

					if (movDir != 0.f)
					{
						if (aii::RandBoolMut(0.5, brain))
						{
							movDir *= -1.f;
						}
					}

					movementDir = movDir;
				}

				Jump(movementDir);
			}
		}
	}
	else 
	{
		velDrag = 1;
	}

	std::cout << movementDir << "\n";

	if (aii::RandBoolMut(0.2, brain))
	{
		if (aii::RandBoolMut(0.6, brain))
		{
			curState = AIState::JustJumpwalkin;
		}
		else if (aii::RandBoolMut(0.3, brain)) 
		{
			curState = AIState::Idle;
		}
		else if (aii::RandBoolMut(0.8, brain))
		{
			curState = AIState::HappyJumping;
		}
	}
}

void AIEntity::Jump(float hdir)
{
	float jforce = -std::sqrt(2.f * world->gravity.y * jumpHeight);

	vel.y = jforce;
	vel.x = hdir*jumpHorSpeed;
}

AIBlockData AIEntity::GetBlock(Vector2I b)
{
	Vector2 wbpos = {pos.x + (float)b.x, pos.y + (float)b.y};
	Vector2I bpos = {(int)wbpos.x, (int)wbpos.y};

	uint16_t blid = world->GetBlock(bpos);

	Block* blc = reg::GetBlock(blid);

	if (blc)
	{
		Vector2 dist =wbpos - pos;
		return {blc->type, Vector2Normalize(dist), Vector2Length(dist)};
	}
	return {false};
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