#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>

class GameCamera
{
	Camera2D thecam = {};
public:
	GameCamera()
	{
		UpdateCamera();
	}
	~GameCamera()
	{

	}

	Vector2 pos = {0, 0};
	float rot = 0;
	float size = 10;

	inline void UpdateCamera()
	{
		thecam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
		thecam.zoom = (float)GetScreenHeight() / (2.0f * size);
		thecam.target = pos;
		thecam.rotation = rot;
	}

	inline Vector2 ScreenToWorld(Vector2 v) const
	{
		return GetScreenToWorld2D(v, thecam);
	}

	inline Vector2 WorldToScreen(Vector2 v) const
	{
		return GetWorldToScreen2D(v, thecam);
	}

	inline Rectangle WorldScreenRect() const
	{
		Vector2 worldTL = ScreenToWorld({0.f, 0.f});
		Vector2 worldBR = ScreenToWorld({(float)GetScreenWidth(), (float)GetScreenHeight()});

		return {worldTL.x, worldTL.y, worldBR.x -worldTL.x, worldBR.y -worldTL.y};
	}

	inline Vector2 WorldToScreenSize(float x, float y)
	{
		Vector2 a = WorldToScreen({0.0f, 0.0f});
		Vector2 b = WorldToScreen({x, y});

		return {
			std::fabs(b.x - a.x),
			std::fabs(b.y - a.y)
		};
	}

	inline Vector2 ScreenToWorldSize(float x, float y)
	{
		Vector2 a = ScreenToWorld({0.0f, 0.0f});
		Vector2 b = ScreenToWorld({x, y});

		return {
			std::fabs(b.x - a.x),
			std::fabs(b.y - a.y)
		};
	}

	inline float WorldToScreenPoint()
	{
		return WorldToScreenSize(1, 0).x;
	}

	inline float ScreenToWorldPoint()
	{
		return ScreenToWorldSize(1, 0).x;
	}

	inline Vector2 WorldScreenTopLeft()
	{
		float w = GetScreenWidth();
		float h = GetScreenHeight();

		return {pos.x - w/2.f, pos.y - h/2.f};
	}

	inline Vector2 WorldScreenTopRight()
	{
		float w = GetScreenWidth();
		float h = GetScreenHeight();

		return {pos.x + w/2.f, pos.y - h/2.f};
	}

	inline Vector2 WorldScreenDownLeft()
	{
		float w = GetScreenWidth();
		float h = GetScreenHeight();

		return {pos.x - w/2.f, pos.y + h/2.f};
	}

	inline Vector2 WorldScreenDownRight()
	{
		float w = GetScreenWidth();
		float h = GetScreenHeight();

		return {pos.x + w/2.f, pos.y + h/2.f};
	}

	inline Camera2D Cam()
	{
		return thecam;
	}
};