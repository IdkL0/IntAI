#include "../Entity.hpp"
#include "raylib.h"

class MovableEntity : public Entity
{
public:
	MovableEntity(World &world) : Entity(world) {};

	Vector2 vel;
	float velDrag = 0.95;
	bool autoMove = true;
	bool collide = true;
	bool useGravity = true;

	virtual void Tick(double dt) override;

	void Move(Vector2 m);
};