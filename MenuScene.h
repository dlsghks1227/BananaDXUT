#pragma once
#include "DXUT.h"
#include "IScene.hpp"

class MenuScene final : public IScene
{
public:
	MenuScene()		noexcept;
	~MenuScene() = default;

	MenuScene(MenuScene&&) = default;
	MenuScene& operator = (MenuScene&&) = default;

	MenuScene(MenuScene const&) = delete;
	MenuScene& operator = (MenuScene const&) = delete;
	

	void OnEnterScene()						override;
	void OnExitScene()						override;

	void OnUpdate(float fElapsedTime)		override;
	void OnLateUpdate(float fElapsedTime)	override;

	void OnRender(float fElapsedTime)		override;

	void OnResetDevice()					override;
	void OnLostDevice()						override;
private:
	CDXUTDialog		m_UI;
};