#pragma once

#include "MovableEntity.hpp"
#include "raylib.h"
#include <cstdint>

#include "../../shared/BlocksRegistry.hpp"
#include "../../shared/Vector2I.hpp"

struct AIBlockData
{
	AIBlockData(bool is)
	{
		this->is = is;
	}
	AIBlockData(BlockType t, Vector2 dt, float d)
	{
		this->t = t;
		dirto = dt;
		dist = d;
		is = true;
	}

	Vector2 dirto;
	float dist;
	BlockType t;
	bool is;
};

class AIEntity : public MovableEntity
{
protected:
	bool CheckGrounded();

	float movementDir = 0.f;
	float jumpHorSpeed = 12.f;
	float jumpHeight = 5.f;
	int visionRadius = 6;

	enum AIState : uint8_t
	{
		Idle,
		JustJumpwalkin,
		HappyJumping,
		WannaSuicide,
		GoToTarget
	};
	AIState curState = JustJumpwalkin;

	AIBlockData GetBlock(Vector2I b);
	void Jump(float hdir = 0.f);
public:
	AIEntity(World &world);

	uint64_t brain;

	virtual void Tick(double dt) override;
};