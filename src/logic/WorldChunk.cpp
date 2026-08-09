#include "WorldChunk.hpp"
#include <cstddef>

uint16_t WorldChunk::GetBlock(const Vector2I& v)
{
	return GetBlock(v.x, v.y);
}

uint16_t WorldChunk::GetBlock(size_t x, size_t y)
{
	if (x >= WORLDCHUNK_XY)
	{
		x = 0;
	}

	if (y >= WORLDCHUNK_XY)
	{
		y = 0;
	}

	size_t i = PosToId(x, y);

	return blocks[i];
}