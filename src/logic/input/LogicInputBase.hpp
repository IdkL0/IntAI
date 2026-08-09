#pragma once

class Logic;

class LogicInputBase
{
protected:
	Logic& logic;

	const float blocksize = 1.f;
public:
	LogicInputBase(Logic& l) : logic(l) {}; 
	virtual ~LogicInputBase() = default;

	virtual void Start() = 0;
	virtual void Update(double dt) = 0;
};