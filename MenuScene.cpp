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

	m_HUD.SetFont(0, L"Comic Sans MS", 30, FW_NORMAL);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_GAMESTART_BUTTON), L"Game Start", 0, 0, 300, 50, VK_RETURN);

	m_HUD.SetFont(0, L"Comic Sans MS", 30, FW_NORMAL);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_EXIT_BUTTON), L"Exit", 0, 70, 300, 50);

	m_UI.SetFont(1, L"±Ã¼­Ã¼", 48, FW_NORMAL);
	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT), L"Hello World!", 0, 0, 600, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->iFont = 1;


}

void MenuScene::OnEnterScene()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation((backBufferSurfaceDesc->Width / 2) - 150, (backBufferSurfaceDesc->Height / 2) + 200);
	m_HUD.SetSize(300, 300);

	m_UI.SetLocation((backBufferSurfaceDesc->Width / 2) - 300, (backBufferSurfaceDesc->Height / 2) - 300);
	m_UI.SetSize(600, 600);
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
