#pragma once

#include "LogicInputBase.hpp"

#include "../Logic.hpp"

class PlayerTimeController : public LogicInputBase
{
	World& world;
	
	const float defScale = 1;
	const float spedScale = 2;
	const float slowScale = 0.5f;
	const float stopScale = 0;

	float before_stop = -1;
public:
	PlayerTimeController(Logic& l) : LogicInputBase(l), world(*l.world) {};

	virtual void Start() override;
	virtual void Update(double dt) override;
};