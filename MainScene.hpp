#pragma once
#include "DXUT.h"
#include "IScene.hpp"
#include "header.hpp"

#include "ObjectCollection.h"
#include "Map.hpp"
#include "Player.hpp"

class MainScene final : public IScene
{
public:
	MainScene() noexcept;
	~MainScene();

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

	void	OnDestroyDevice()					override;

	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext) override;

private:
	ObjectCollection			m_objectCollection;
	//std::shared_ptr<Player>		m_player;
	//std::shared_ptr<Map>		m_map;

	bool	m_isInside;
	RECT	m_addRect;
};