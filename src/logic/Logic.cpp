#include "Logic.hpp"

#include "../shared/Game/GameBlocks.hpp"
#include "Entity.hpp"
#include "input/PlayerCameraController.hpp"
#include "input/PlayerWorldController.hpp"
#include "input/PlayerEntityController.hpp"
#include <memory>
#include <utility>

#include "../shared/RngEngine.hpp"

#include "entities/MovableEntity.hpp"

void Logic::Init()
{
	world = new World();

	gamereg::RegisterBlocks();

	AddInput<PlayerCameraController>();
	AddInput<PlayerWorldController>();
	AddInput<PlayerEntityController>();

	// for (int i = 0; i < 128; i++)
	// {
	// 	auto ent = std::make_unique<Entity>(*world);
	// 	ent->pos = {rng::RandFloat(0, 512), rng::RandFloat(10, 502)};

	// 	world->entities.push_back(std::move(ent));
	// }
}

Logic::~Logic()
{
	delete world;
}

void Logic::Update(double dt)
{
	for (const auto& input : inputs) 
	{
    	input->Update(dt);
	}

	accumulator += dt;

	while (accumulator >= GetTickTime())
	{
		Tick();
		accumulator -= GetTickTime();
	}
}

void Logic::Tick()
{
	world->Tick(GetTickTime());
}

double Logic::GetTickTime()
{
	return 1./tickrate;
}

void Logic::SetTickRate(uint32_t rate)
{
	tickrate = rate;
}