#pragma once

#include "Entity.hpp"
#include "WorldChunk.hpp"
#include "../shared/Vector2I.hpp"
#include "raylib.h"
#include <cstddef>
#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

#define WORLD_CHUNKS_XY 16

class World
{
public:
	WorldChunk chunks[WORLD_CHUNKS_XY*WORLD_CHUNKS_XY]{};

	std::vector<std::unique_ptr<Entity>> entities;

	Vector2 gravity = {0, 9.81f};
	float timeScale = 1;

	void Tick(double dt);

	WorldChunk& GetChunk(const Vector2I& v);
	WorldChunk& GetChunk(size_t x, size_t y);

	uint16_t GetBlock(const Vector2I& v);
	uint16_t GetBlock(size_t x, size_t y);

	inline size_t PosToId(const Vector2I& v)
	{
		return PosToId(v.x, v.y);
	}

	inline size_t PosToId(size_t x, size_t y) const
	{
		return y * WORLD_CHUNKS_XY + x;
	}

	inline Vector2I IdToPos(size_t i) const
	{
		int x = i % WORLD_CHUNKS_XY;
		int y = std::floor(i / WORLD_CHUNKS_XY);

		return {x, y};
	}

	inline Vector2I WorldToWorldBlock(Vector2 v) const
	{
		return {
			static_cast<int>(std::floor(v.x)),
			static_cast<int>(std::floor(v.y))
		};
	}

	inline Vector2I WorldBlockToBlock(Vector2I v) const
	{
		return {
			v.x % WORLDCHUNK_XY,
			v.y % WORLDCHUNK_XY
		};
	}

	inline Vector2I WorldBlockToChunk(Vector2I v) const
	{
		return {
			static_cast<int>(std::floor(static_cast<float>(v.x) / WORLDCHUNK_XY)),
			static_cast<int>(std::floor(static_cast<float>(v.y) / WORLDCHUNK_XY))
		};
	}

	inline size_t WorldBlockChunk(Vector2I v) const
	{
		Vector2I chunk = WorldBlockToChunk(v);

		return PosToId(static_cast<size_t>(chunk.x), static_cast<size_t>(chunk.y));
	}
};