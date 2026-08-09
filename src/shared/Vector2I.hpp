#pragma once

struct Vector2I
{
	Vector2I() {}
	Vector2I(int x = 0, int y = 0) : x(x), y(y) {}

	int x = 0;
	int y = 0;

	Vector2I operator+(const Vector2I& other) const 
	{
        return {x + other.x, y + other.y};
    }

	Vector2I operator-(const Vector2I& other) const 
	{
        return {x - other.x, y - other.y};
    }
};