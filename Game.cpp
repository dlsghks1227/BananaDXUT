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
	m_HUD.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_TOGGLEFULLSCREEN), L"Toggle full screen", 35, 10, 125, 22);

	m_menuScene = std::make_shared<MenuScene>();
	m_mainScene = std::make_shared<MainScene>();

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
	m_sceneStateMachine.SwitchTo(L"MainScene");
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
	m_HUD.OnRender(fElapsedTime);

	m_sceneStateMachine.OnRender(fElapsedTime);
}

void Game::OnResetDevice()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation(backBufferSurfaceDesc->Width - 170, 0);
	m_HUD.SetSize(170, 170);
}

void Game::OnLostDevice()
{
	m_sceneStateMachine.OnLostDevice();
}

void Game::OnDestoryDevice()
{
	m_sceneStateMachine.OnDestoryDevice();
}


LRESULT Game::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}