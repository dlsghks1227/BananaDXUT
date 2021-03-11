#pragma once
#include "DXUT.h"

__interface IScene
{
	void		OnEnterScene();
	void		OnExitScene();

	void		OnUpdate(float fElapsedTime);
	void		OnLateUpdate(float fElapsedTime);

	void		OnRender(float fElapsedTime);

	void		OnResetDevice();
	void		OnLostDevice();

	void		OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext);
	void		OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);

	LRESULT		MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);
};