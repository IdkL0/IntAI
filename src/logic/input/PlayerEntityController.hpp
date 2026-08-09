#pragma once

#include "LogicInputBase.hpp"

#include "../Logic.hpp"

class PlayerEntityController : public LogicInputBase
{
	World& world;
public:
	PlayerEntityController(Logic& l) : LogicInputBase(l), world(*l.world) {};

	virtual void Start() override;
	virtual void Update(double dt) override;
};