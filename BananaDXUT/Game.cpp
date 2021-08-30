#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"
#include "Game.hpp"

#include "event.hpp"

extern CModelViewerCamera			g_camera;
extern CDXUTDialogResourceManager	g_dialogResourceManager;

Game::Game() noexcept
{
	m_menuScene			= std::make_shared<MenuScene>();
	m_stage1Scene		= std::make_shared<Stage1Scene>(m_textureAllocator, m_sceneStateMachine);
	m_stage2Scene		= std::make_shared<Stage2Scene>(m_textureAllocator, m_sceneStateMachine);
	m_gameOverScene		= std::make_shared<GameOverScene>();
	m_gameClearScene	= std::make_shared<GameClearScene>();

	m_sceneStateMachine.Add(L"MenuScene",		m_menuScene);
	m_sceneStateMachine.Add(L"Stage1Scene",		m_stage1Scene);
	m_sceneStateMachine.Add(L"Stage2Scene",		m_stage2Scene);
	m_sceneStateMachine.Add(L"GameOverScene",	m_gameOverScene);
	m_sceneStateMachine.Add(L"GameClearScene",	m_gameClearScene);
}

Game::~Game()
{
	m_menuScene.reset();
	m_stage1Scene.reset();
	m_stage2Scene.reset();
	m_gameOverScene.reset();
	m_gameClearScene.reset();
}

void Game::OnCreateDevice()
{
	m_sceneStateMachine.SwitchTo(L"MenuScene");
}

void Game::OnUpdate(float fElapsedTime)
{
	m_sceneStateMachine.OnUpdate(fElapsedTime);

	if (g_inputManager->GetKeyPressed(DIK_F4) == true)
	{
		m_sceneStateMachine.SwitchTo(L"MenuScene");

	}
	if (g_inputManager->GetKeyPressed(DIK_F5) == true)
	{
		m_sceneStateMachine.SwitchTo(L"Stage1Scene");

	}
	if (g_inputManager->GetKeyPressed(DIK_F6) == true)
	{
		m_sceneStateMachine.SwitchTo(L"Stage2Scene");

	}
}

void Game::OnLateUpdate(float fElapsedTime)
{
	m_sceneStateMachine.OnLateUpdate(fElapsedTime);
}

void Game::OnRender(float fElapsedTime)
{
	m_sceneStateMachine.OnRender(fElapsedTime);
}

void Game::OnUIRender(float fElapsedTime)
{
	m_sceneStateMachine.OnUIRender(fElapsedTime);
}

void Game::OnResetDevice()
{
	m_sceneStateMachine.OnResetDevice();
}

void Game::OnLostDevice()
{
	m_sceneStateMachine.OnLostDevice();
}

void Game::OnDestoryDevice()
{
	m_textureAllocator.AllRemove();
	m_sceneStateMachine.OnDestoryDevice();
}


LRESULT Game::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	m_sceneStateMachine.MsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing, pUserContext);
	return 0;
}

void Game::ChangeScene(std::wstring const& name)
{
	m_sceneStateMachine.SwitchTo(name);
}