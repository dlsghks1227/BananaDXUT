#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"
#include "header.hpp"

class Game final
{
public:
	Game() noexcept;
	~Game() = default;

	Game(Game&&) = default;
	Game& operator = (Game&&) = default;

	Game(Game const&) = delete;
	Game& operator = (Game const&) = delete;

	void Initialize();

	void OnUpdate(float fElapsedTime);
	void OnLateUpdate(float fElapsedTime);

	void OnRender(float fElapsedTime);

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

	void OnResetDevice();
	void OnLostDevice();

	void OnDestoryDevice();

public:
	CDXUTDialog					m_HUD;
};