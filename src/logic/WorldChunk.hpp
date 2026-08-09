#pragma once

#include "../shared/Vector2I.hpp"
#include <cstdint>
#include <cmath>

#define WORLDCHUNK_XY 32

class WorldChunk
{
public:
	inline WorldChunk()
	{
		for (size_t i = 0; i < WORLDCHUNK_XY * WORLDCHUNK_XY; ++i)
		{
			blocks[i] = 0;
		}
	}

	uint16_t blocks[WORLDCHUNK_XY*WORLDCHUNK_XY]{};

	uint16_t GetBlock(const Vector2I& v);
	uint16_t GetBlock(size_t x, size_t y);
	
	inline size_t PosToId(const Vector2I& v) const
	{
		return PosToId(v.x, v.y);
	}

	inline size_t PosToId(size_t x, size_t y) const
	{
		return y * WORLDCHUNK_XY + x;
	}

	inline Vector2I IdToPos(size_t i) const
	{
		int x = i % WORLDCHUNK_XY;
		int y = std::floor(i / WORLDCHUNK_XY);

		return {x, y};
	}
};