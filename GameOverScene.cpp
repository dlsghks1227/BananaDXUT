#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"

#include "GameOverScene.hpp"


extern CDXUTDialogResourceManager	g_dialogResourceManager;

GameOverScene::GameOverScene() noexcept
{
	m_HUD.Init(&g_dialogResourceManager);
	m_UI.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_UI.SetCallback(OnGUIEvent);

	m_HUD.SetFont(0, L"Comic Sans MS", 30, FW_NORMAL);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_MENU_BUTTON), L"Menu", 0, 0, 300, 50, VK_RETURN);

	m_UI.SetFont(1, L"Comic Sans MS", 48, FW_NORMAL);
	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT), L"Game Over", 0, 0, 600, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->iFont = 1;


}

void GameOverScene::OnEnterScene()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation((backBufferSurfaceDesc->Width / 2) - 150, (backBufferSurfaceDesc->Height / 2) + 200);
	m_HUD.SetSize(300, 300);

	m_UI.SetLocation((backBufferSurfaceDesc->Width / 2) - 300, (backBufferSurfaceDesc->Height / 2) - 300);
	m_UI.SetSize(600, 600);
}

void GameOverScene::OnExitScene()
{
}

void GameOverScene::OnUpdate(float fElapsedTime)
{
}

void GameOverScene::OnLateUpdate(float fElapsedTime)
{
}

void GameOverScene::OnRender(float fElapsedTime)
{
}

void GameOverScene::OnUIRender(float fElapsedTime)
{
	m_HUD.OnRender(fElapsedTime);
	m_UI.OnRender(fElapsedTime);
}

void GameOverScene::OnResetDevice()
{
}

void GameOverScene::OnLostDevice()
{
}

void GameOverScene::OnDestroyDevice()
{
}

LRESULT GameOverScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	*pbNoFurtherProcessing = m_UI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}
