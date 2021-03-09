#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"
#include "Game.hpp"

#include "event.hpp"

extern CModelViewerCamera			g_camera;
extern CDXUTDialogResourceManager	g_dialogResourceManager;

extern void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContexts);

Game::Game() noexcept
{

}

void Game::Initialize()
{
	m_HUD.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_HUD.AddButton(static_cast<int>(GUI_EVENT::IDC_TOGGLEFULLSCREEN), L"Toggle full screen", 35, 10, 125, 22);	
}

void Game::OnUpdate(float fElapsedTime)
{
}

void Game::OnLateUpdate(float fElapsedTime)
{
}

void Game::OnRender(float fElapsedTime)
{
	m_HUD.OnRender(fElapsedTime);
}

LRESULT Game::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}

void Game::OnResetDevice()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation(backBufferSurfaceDesc->Width - 170, 0);
	m_HUD.SetSize(170, 170);
}

void Game::OnLostDevice()
{
}

void Game::OnDestoryDevice()
{
}
