#include "PlayerWorldController.hpp"

#include <raylib.h>

#include "../../shared/CameraMng.hpp"

void PlayerWorldController::Start()
{

}

void PlayerWorldController::Update(double dt)
{
	if (!CameraMng::Camr()) return;

	Vector2 mousePos = CameraMng::curCam->ScreenToWorld(GetMousePosition());

	Vector2I blockPos = {(int)mousePos.x, (int)mousePos.y};

	Vector2I pos = world.WorldToWorldBlock(mousePos);
	Vector2I chunkPos = world.WorldBlockToChunk(pos);
	
	if (chunkPos.x >= 0 && chunkPos.x < WORLD_CHUNKS_XY && 
	    chunkPos.y >= 0 && chunkPos.y < WORLD_CHUNKS_XY)
	{
		Vector2I localpos = world.WorldBlockToBlock(pos);
		WorldChunk& chunk = world.chunks[world.PosToId(chunkPos)];

		for (int i = 1; i <= 10; ++i) 
		{
            int key = (i == 10) ? KEY_ZERO : (KEY_ONE + i - 1);
            
            if (IsKeyDown(key)) 
			{
				chunk.blocks[chunk.PosToId(localpos)] = i;
            }
        }
		if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
		{
			chunk.blocks[chunk.PosToId(localpos)] = 0;
		}

		// std::cout << "chunk x: " << world.WorldBlockToChunk(pos).x << " chunk y: " << world.WorldBlockToChunk(pos).y << '\n' 
		// 	<< "block x:" << pos.x << " block y: " << pos.y << " block: " << chunk.blocks[chunk.PosToId(localpos)] << '\n';
	}
}