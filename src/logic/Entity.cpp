#include "Entity.hpp"

Entity::Entity(World& world)
{
	this->world = &world;
}

Entity::~Entity()
{
	
}

void Entity::Tick(double dt)
{
	
}