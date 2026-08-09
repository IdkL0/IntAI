#pragma once

#include "../BlocksRegistry.hpp"

namespace blocks
{
	struct Air : public Block {};

	struct Tile : public Block 
	{
		inline Tile()
		{
			name = "Tile";
			texture_path = "textures/blocks/tile.png";
			solid = true;
		}
	};

	struct TestTile : public Block 
	{
		inline TestTile()
		{
			name = "TestTile";
			texture_path = "textures/blocks/testtile.png";
			solid = true;
		}
	};

	struct Beznazvaniya : public Block 
	{
		inline Beznazvaniya()
		{
			name = "Beznazvaniya";
			texture_path = "textures/blocks/beznazvaniya.png";
			solid = true;
		}
	};
}

namespace gamereg
{
	inline void RegisterBlocks()
	{
		reg::RegisterBlock<blocks::Air>();
		reg::RegisterBlock<blocks::Tile>();
		reg::RegisterBlock<blocks::TestTile>();
		reg::RegisterBlock<blocks::Beznazvaniya>();
	}
}