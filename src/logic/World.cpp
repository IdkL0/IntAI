#include "World.hpp"
#include "WorldChunk.hpp"
#include <cstddef>
#include <cstdint>

void World::Tick(double dt)
{
    if (timeScale == 0) return;

	for (auto& ent : entities)
	{
		ent->Tick(dt);
	}
}

WorldChunk& World::GetChunk(const Vector2I& v)
{
	return GetChunk(v.x, v.y);
}

WorldChunk& World::GetChunk(size_t x, size_t y)
{
	if (x >= WORLD_CHUNKS_XY * WORLDCHUNK_XY ||
        y >= WORLD_CHUNKS_XY * WORLDCHUNK_XY)
    {
        return chunks[0];
    }

	size_t i = PosToId(x, y);

	return chunks[i];
}

uint16_t World::GetBlock(const Vector2I& v)
{
	return GetBlock(v.x, v.y);
}

uint16_t World::GetBlock(size_t x, size_t y)
{
    if (x >= WORLD_CHUNKS_XY * WORLDCHUNK_XY ||
        y >= WORLD_CHUNKS_XY * WORLDCHUNK_XY)
    {
        return 0;
    }

    auto chunk = GetChunk(WorldBlockChunk({(int)x, (int)y}));
    Vector2I local = WorldBlockToBlock({(int)x, (int)y});
    return chunk.GetBlock(local);
}