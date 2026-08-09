#pragma once

#include "raylib.h"
#include <cmath>

namespace aabb 
{
	inline bool Box(Rectangle a, Rectangle b)
	{
		return a.x + a.width > b.x && 
			a.x < b.x + b.width &&
			a.y + a.height > b.y && 
			a.y < b.y + b.height;
	}

	inline bool Point(Rectangle a, Vector2 b)
	{
		return a.x <= b.x &&
			a.x + a.width >= b.x &&
			a.y <= b.y &&
			a.y + a.height >= b.y;
	}

	inline bool Line(Rectangle a, Vector2 v0, Vector2 v1, Vector2& vecIntersect, float& fraction)
	{
		float tmin = 0.0f;
		float tmax = 1.0f;

		float dx = v1.x - v0.x;
		float dy = v1.y - v0.y;

		const float eps = 1e-8f;

		if (std::fabs(dx) < eps) 
		{
			if (v0.x < a.x || v0.x > a.x + a.width) return false;
		} 
		else 
		{
			float inv = 1.0f / dx;
			float t1 = (a.x - v0.x) * inv;
			float t2 = (a.x + a.width - v0.x) * inv;
			float ta = fminf(t1, t2);
			float tb = fmaxf(t1, t2);
			tmin = fmaxf(tmin, ta);
			tmax = fminf(tmax, tb);
			if (tmin > tmax) return false;
		}

		if (std::fabs(dy) < eps) 
		{
			if (v0.y < a.y || v0.y > a.y + a.height) return false;
		} 
		else 
		{
			float inv = 1.0f / dy;
			float t1 = (a.y - v0.y) * inv;
			float t2 = (a.y + a.height - v0.y) * inv;
			float ta = fminf(t1, t2);
			float tb = fmaxf(t1, t2);
			tmin = fmaxf(tmin, ta);
			tmax = fminf(tmax, tb);
			if (tmin > tmax) return false;
		}

		if (tmax < 0.0f || tmin > 1.0f) return false;

		if (tmin < 0.0f) 
		{
			fraction = 0.0f;
			vecIntersect = v0;
			return true;
		}

		fraction = tmin;
		vecIntersect.x = v0.x + (v1.x - v0.x) * fraction;
		vecIntersect.y = v0.y + (v1.y - v0.y) * fraction;
		return true;
	}
}