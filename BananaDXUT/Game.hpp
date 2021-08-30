#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"
#include "header.hpp"

#include "SceneStateMachine.hpp"

#include "MenuScene.hpp"
#include "Stage1Scene.hpp"
#include "Stage2Scene.hpp"
#include "GameOverScene.hpp"
#include "GameClearScene.hpp"

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

	void		ChangeScene(std::wstring const& name);
private:
	ResourceAllocator<Texture>	m_textureAllocator;

	SceneStateMachine				m_sceneStateMachine;
	std::shared_ptr<MenuScene>		m_menuScene;
	std::shared_ptr<Stage1Scene>	m_stage1Scene;
	std::shared_ptr<Stage2Scene>	m_stage2Scene;
	std::shared_ptr<GameOverScene>	m_gameOverScene;
	std::shared_ptr<GameClearScene>	m_gameClearScene;
};