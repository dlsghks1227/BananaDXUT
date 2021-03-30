#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"

#include "event.hpp"
#include "MenuScene.hpp"

extern CDXUTDialogResourceManager	g_dialogResourceManager;

MenuScene::MenuScene() noexcept
{
	m_HUD.Init(&g_dialogResourceManager);
	m_UI.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_UI.SetCallback(OnGUIEvent);

	m_HUD.SetFont(1, L"Comic Sans MS", 48, FW_NORMAL);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_GAMESTART_BUTTON), L"asdasd", 0, 0, 300, 50);
	m_HUD.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_GAMESTART_BUTTON))->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
	m_HUD.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_GAMESTART_BUTTON))->GetElement(0)->iFont = 1;
	m_HUD.Refresh();

	m_UI.SetFont(1, L"Comic Sans MS", 48, FW_NORMAL);
	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT), L"Game", 300, 300, 620, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->iFont = 1;
	m_UI.Refresh();
}

void MenuScene::OnEnterScene()
{
}

void MenuScene::OnExitScene()
{
}

void MenuScene::OnUpdate(float fElapsedTime)
{
}

void MenuScene::OnLateUpdate(float fElapsedTime)
{
}

void MenuScene::OnRender(float fElapsedTime)
{
}

void MenuScene::OnUIRender(float fElapsedTime)
{
	m_HUD.OnRender(fElapsedTime);
	m_UI.OnRender(fElapsedTime);
}

void MenuScene::OnResetDevice()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation(backBufferSurfaceDesc->Width / 2, backBufferSurfaceDesc->Height / 2);
	m_HUD.SetSize(170, 170);

	m_UI.SetLocation(0, 0);
	m_UI.SetSize(backBufferSurfaceDesc->Width, backBufferSurfaceDesc->Height);
}

void MenuScene::OnLostDevice()
{
}

void MenuScene::OnDestroyDevice()
{
}

LRESULT MenuScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	*pbNoFurtherProcessing = m_UI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}
