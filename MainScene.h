#pragma once
#include "DXUT.h"
#include "IScene.hpp"

class MainScene final : public IScene
{
public:
	MainScene() noexcept;
	~MainScene() = default;

	MainScene(MainScene&&) = default;
	MainScene& operator = (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator = (MainScene const&) = delete;

	void	OnEnterScene()						override;
	void	OnExitScene()						override;

	void	OnUpdate(float fElapsedTime)		override;
	void	OnLateUpdate(float fElapsedTime)	override;

	void	OnRender(float fElapsedTime)		override;

	void	OnResetDevice()						override;
	void	OnLostDevice()						override;

	void	OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext) override;
	void	OnMouse(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext) override;

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext) override;

private:

};