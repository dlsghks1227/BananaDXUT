#pragma once
#include "DXUT.h"

__interface IScene
{
	void		OnEnterScene();
	void		OnExitScene();

	void		OnUpdate(float fElapsedTime);
	void		OnLateUpdate(float fElapsedTime);

	void		OnRender(float fElapsedTime);
	void		OnUIRender(float fElapsedTime);

	void		OnResetDevice();
	void		OnLostDevice();

	void		OnDestroyDevice();

	LRESULT		MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
};