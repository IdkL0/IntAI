#pragma once

#include <vector>
#include "GameCamera.hpp"

class CameraMng
{
public:
	CameraMng() = default;
	~CameraMng() = default;
	
	inline static std::vector<GameCamera*> cams;
	inline static GameCamera* curCam = nullptr;

	inline static void SetupCamera()
	{
		GameCamera* cam = new GameCamera();

		cams.push_back(cam);
		curCam = cam;
	}

	inline static bool Camr()
	{
		return curCam != nullptr;
	}

	inline static void UpdCam()
	{
		if (Camr())
		{
			curCam->UpdateCamera();
		}
	}

	inline static void DESTROY()
	{
		for (auto cam : cams)
		{
			delete cam;
		}
		cams.clear();
		curCam = nullptr;
	}
};