#pragma once

#include "LogicInputBase.hpp"

#include "../Logic.hpp"

class PlayerWorldController : public LogicInputBase
{
	World& world;
public:
	PlayerWorldController(Logic& l) : LogicInputBase(l), world(*l.world) {};

	virtual void Start() override;
	virtual void Update(double dt) override;
};