#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "World.hpp"
#include "input/LogicInputBase.hpp"

class Logic
{
	double accumulator = 0;
	uint32_t tickrate = 60;

	void Tick();

	double GetTickTime();
public:
	Logic() = default;
	~Logic();
	Logic(const Logic &) = default;
	Logic(Logic &&) = default;
	Logic &operator=(const Logic &) = default;
	Logic &operator=(Logic &&) = default;
  
	void Init();

	void Update(double dt);

	void SetTickRate(uint32_t rate);

	template<typename T>
	inline void AddInput()
	{
		std::unique_ptr<LogicInputBase> input = std::make_unique<T>(*this);
		input->Start();
		inputs.push_back(std::move(input));
	}
	
	World* world;

	std::vector<std::unique_ptr<LogicInputBase>> inputs;
};