#pragma once

#include "MovableEntity.hpp"
#include <cstdint>

class AIEntity : public MovableEntity
{
protected:
	bool CheckGrounded();
public:
	AIEntity(World &world) : MovableEntity(world) {};

	uint64_t brain;

	virtual void Tick(double dt) override;
};