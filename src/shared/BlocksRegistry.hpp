#pragma once

#include "raylib.h"
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Block
{
	virtual ~Block() = default;
	
	uint16_t id = 0;
	std::string name = "Air";
	std::string texture_path = ""; 
	bool solid = false;
	bool interactable = false;
	bool dynamic = false;
	Rectangle hitbox = {0, 0, 1, 1};

	virtual void EntCollide() {};

	virtual void Interact() {};

	virtual void Tick() {};
};

class BlocksRegistry
{
public:
	BlocksRegistry() = delete;
	~BlocksRegistry() = delete;

	inline static std::vector<std::unique_ptr<Block>> regs;

	template<typename T>
	inline static uint16_t Register()
	{
		uint16_t newid = regs.size();

		std::unique_ptr<Block> block = std::make_unique<T>();
		block->id = newid;

		regs.push_back(std::move(block));

		return newid;
	};

	inline static Block* GetBlock(uint16_t id)
	{
		if (id >= regs.size())
		{
			return nullptr;
		}

		return regs[id].get();
	};
};

namespace reg
{
	template<typename T>
	inline uint16_t RegisterBlock()
	{
		return BlocksRegistry::Register<T>();
	}

	inline Block* GetBlock(uint16_t id)
	{
		return BlocksRegistry::GetBlock(id);
	}
}