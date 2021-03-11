#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"

#include "event.hpp"
#include "MenuScene.h"

extern CDXUTDialogResourceManager	g_dialogResourceManager;

MenuScene::MenuScene() noexcept
{
	//m_UI.Init(&g_dialogResourceManager);

	//m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_STATIC), L"Menu Scene", 0, 0, 200, 30);
	//m_UI.GetStatic(static_cast<int>(UI_CONTROL_ID::IDC_STATIC))->SetTextColor(D3DCOLOR_XRGB(255, 0, 0));
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

void MenuScene::OnResetDevice()
{
}

void MenuScene::OnLostDevice()
{
}

void MenuScene::OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext)
{
}

void MenuScene::OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
}

LRESULT MenuScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return LRESULT();
}
