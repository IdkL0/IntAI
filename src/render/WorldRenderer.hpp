#pragma once

#include "../logic/World.hpp"

#include "../shared/BlocksRegistry.hpp"
#include "../shared/ResourcesMng.hpp"
#include "../shared/CameraMng.hpp"

#include "../shared/AABBHelper.hpp"

#include <algorithm>
#include <cmath>
#include <raylib.h>

namespace render 
{
	inline void RenderWorld(const World& world)
	{
		if (!CameraMng::Camr())
		{
			return;
		}

		const GameCamera* cam = CameraMng::curCam;
		float blocksize = 1.f;
		float chunksize = WORLDCHUNK_XY * blocksize;

		Rectangle worldSc = cam->WorldScreenRect();

		Rectangle worldRect = {0, 0, (float)(WORLD_CHUNKS_XY*WORLDCHUNK_XY)+1.f, (float)(WORLD_CHUNKS_XY*WORLDCHUNK_XY)+1.f};

		if (!aabb::Box(worldSc, worldRect)) return;

		int left = static_cast<int>(std::floor(worldSc.x));
		int top = static_cast<int>(std::floor(worldSc.y));
		int right = static_cast<int>(std::ceil(worldSc.x + worldSc.width));
		int bottom = static_cast<int>(std::ceil(worldSc.y + worldSc.height));

		int worldW = WORLD_CHUNKS_XY * WORLDCHUNK_XY;
		int worldH = WORLD_CHUNKS_XY * WORLDCHUNK_XY;

		left = std::max(0, left);
		top = std::max(0, top);
		right = std::min(worldW, right);
		bottom = std::min(worldH, bottom);

		for (int worldY = top; worldY < bottom; ++worldY)
		{
			int chunkY = worldY / WORLDCHUNK_XY;
			int localY = worldY % WORLDCHUNK_XY;

			for (int worldX = left; worldX < right; ++worldX)
			{
				int chunkX = worldX / WORLDCHUNK_XY;
				int localX = worldX % WORLDCHUNK_XY;

				const WorldChunk& chunk = world.chunks[world.PosToId(chunkX, chunkY)];
				uint16_t blockID = chunk.blocks[chunk.PosToId(localX, localY)];

				if (blockID == 0 || blockID >= BlocksRegistry::regs.size())
				{
					continue;
				}

				float worldRenderX = static_cast<float>(worldX) * blocksize;
				float worldRenderY = static_cast<float>(worldY) * blocksize;

				Rectangle source = ResourcesManager::GetBlockAtlasRect(blockID);
				Rectangle dest = {worldRenderX, worldRenderY, blocksize, blocksize};

				DrawTexturePro(ResourcesManager::GetBlocksAtlas(), source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
			}
		}
	}

	inline void RenderEntities(const World& world)
	{
		if (!CameraMng::Camr())
		{
			return;
		}

		const GameCamera* cam = CameraMng::curCam;

		Rectangle worldSc = cam->WorldScreenRect();

		Rectangle worldRect = {0, 0, (float)(WORLD_CHUNKS_XY*WORLDCHUNK_XY)+1.f, (float)(WORLD_CHUNKS_XY*WORLDCHUNK_XY)+1.f};

		if (!aabb::Box(worldSc, worldRect)) return;
		
		for (auto& ent : world.entities)
		{
			Vector2 pos = ent->pos;
			Rectangle box = ent->box;

			Rectangle wrldBox = {pos.x + box.x, pos.y + box.y, box.width, box.width};

			if (!aabb::Box(worldSc, wrldBox)) continue;

			DrawLineV({pos.x-0.5f, pos.y}, {pos.x+0.5f, pos.y}, YELLOW);
			DrawLineV({pos.x, pos.y-0.5f}, {pos.x, pos.y+0.5f}, YELLOW);

			DrawLineV({wrldBox.x, 				wrldBox.y}, 				{wrldBox.x + box.width, 	wrldBox.y}, GREEN);
			DrawLineV({wrldBox.x + box.width, 	wrldBox.y}, 				{wrldBox.x + box.width, 	wrldBox.y + box.height}, GREEN);
			DrawLineV({wrldBox.x + box.width, 	wrldBox.y + box.height}, {wrldBox.x, 				wrldBox.y + box.height}, GREEN);
			DrawLineV({wrldBox.x, 				wrldBox.y + box.height}, {wrldBox.x, 				wrldBox.y}, GREEN);
		}
	}
}