#pragma once

#include "raylib.h"

class World;

class Entity
{
protected:
	World* world = nullptr;
public:
	Entity(World& world);
	virtual ~Entity();
	Entity &operator=(const Entity &) = default;
	Entity &operator=(Entity &&) = default;

	Rectangle box = {-0.5f, -0.5f, 1.f, 1.f};
	Vector2 pos = {0, 0};

	virtual void Tick(double dt);
};