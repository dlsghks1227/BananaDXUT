#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"
#include "header.hpp"

#include "SceneStateMachine.hpp"
#include "MenuScene.hpp"
#include "MainScene.hpp"

class Game final
{
public:
	Game() noexcept;
	~Game();

	Game(Game&&) = default;
	Game& operator = (Game&&) = default;

	Game(Game const&) = delete;
	Game& operator = (Game const&) = delete;

	void		OnCreateDevice();

	void		OnUpdate(float fElapsedTime);
	void		OnLateUpdate(float fElapsedTime);

	void		OnRender(float fElapsedTime);
	void		OnUIRender(float fElapsedTime);

	void		OnResetDevice();
	void		OnLostDevice();

	void		OnDestoryDevice();

	LRESULT		MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext);

private:
	ResourceAllocator<Texture>	m_textureAllocator;

	SceneStateMachine			m_sceneStateMachine;
	std::shared_ptr<MenuScene>	m_menuScene;
	std::shared_ptr<MainScene>	m_mainScene;
};