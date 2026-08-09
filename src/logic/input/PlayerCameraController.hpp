#pragma once

#include "LogicInputBase.hpp"
#include "../../shared/CameraMng.hpp"
#include "raylib.h"

class PlayerCameraController : public LogicInputBase
{
	GameCamera& cam;

	Vector2 lastMousePos;

	float zoomCoef = 0.15f;
	float minSize = 1.0f;
	float maxSize = 200.f;
public:
	PlayerCameraController(Logic& l) : LogicInputBase(l), cam(*CameraMng::curCam) {};

	inline virtual void Start() override
	{
		lastMousePos = GetMousePosition();
	}

	inline virtual void Update(double dt) override
	{
		if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
		{
			Vector2 mousePos = GetMousePosition();

			Vector2 mouseWorld = cam.ScreenToWorld(mousePos);
			Vector2 lastMouseWorld = cam.ScreenToWorld(lastMousePos);

			cam.pos -= mouseWorld - lastMouseWorld;

			lastMousePos = mousePos;
		}
		else 
		{
			lastMousePos = GetMousePosition();
		}

		float scroll = GetMouseWheelMove();

		if (scroll != 0)
		{
			Vector2 mousePos = GetMousePosition();
			Vector2 bzoom = cam.ScreenToWorld(mousePos);

			float scale = 1.0f - scroll * zoomCoef;
			if (scale <= 0.0f) scale = 0.1f;

			//cam.size = std::clamp(cam.size * scale, minSize, maxSize);
			cam.size = cam.size * scale;
			cam.UpdateCamera();

			Vector2 azoom = cam.ScreenToWorld(mousePos);
			cam.pos += bzoom - azoom;
			cam.UpdateCamera();
		}
	}
};