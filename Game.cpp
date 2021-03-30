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
	m_menuScene = std::make_shared<MenuScene>();
	m_mainScene = std::make_shared<MainScene>(m_textureAllocator);

	m_sceneStateMachine.Add(L"MenuScene", m_menuScene);
	m_sceneStateMachine.Add(L"MainScene", m_mainScene);
}

Game::~Game()
{
	m_menuScene.reset();
	m_mainScene.reset();
}

void Game::OnCreateDevice()
{
	m_sceneStateMachine.SwitchTo(L"MenuScene");
	m_sceneStateMachine.SwitchTo(L"MainScene");
	m_sceneStateMachine.SwitchTo(L"MenuScene");

}

void Game::OnUpdate(float fElapsedTime)
{
	m_sceneStateMachine.OnUpdate(fElapsedTime);
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