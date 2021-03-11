#pragma once
#include "DXUT.h"

__interface IScene
{
	void OnEnterScene();
	void OnExitScene();

	void OnUpdate(float fElapsedTime);
	void OnLateUpdate(float fElapsedTime);

	void OnRender(float fElapsedTime);

	void OnResetDevice();
	void OnLostDevice();
};