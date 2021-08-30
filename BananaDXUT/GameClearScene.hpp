#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTCamera.h"
#include "DXUTsettingsdlg.h"

#include "IScene.hpp"

#include "Event.hpp"


class GameClearScene final : public IScene
{
public:
	GameClearScene() noexcept;
	~GameClearScene() = default;

	GameClearScene(GameClearScene&&) = default;
	GameClearScene& operator = (GameClearScene&&) = default;

	GameClearScene(GameClearScene const&) = delete;
	GameClearScene& operator = (GameClearScene const&) = delete;

	void	OnEnterScene()						override;
	void	OnExitScene()						override;

	void	OnUpdate(float fElapsedTime)		override;
	void	OnLateUpdate(float fElapsedTime)	override;

	void	OnRender(float fElapsedTime)		override;
	void	OnUIRender(float fElapsedTime)		override;

	void	OnResetDevice()						override;
	void	OnLostDevice()						override;

	void	OnDestroyDevice()					override;

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext) override;

private:
	CDXUTDialog							m_HUD;
	CDXUTDialog							m_UI;

};