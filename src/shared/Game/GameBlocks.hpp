#pragma once

#include <iostream>

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

	struct Spike : public Block
	{
		inline Spike()
		{
			name = "Spike";
			texture_path = "textures/blocks/spike.png";
			solid = true;
			type = YOUWILLDIE;
			collideEvent = true;
			hitbox = {0.3, 0.2, 0.4, 0.6};
		}

		virtual void EntCollide(World& w, Entity& e, size_t x, size_t y) override
		{
			//kill entity
			std::cout << "I WANT KILL ENTITY!!! -Spike \n";
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
		reg::RegisterBlock<blocks::Spike>();
	}
}