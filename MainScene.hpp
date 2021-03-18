#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "IScene.hpp"

#include "ResourceAllocator.hpp"

#include "Object.hpp"
#include "ObjectCollection.h"

#include "Transform.hpp"
#include "Sprite.hpp"

#include "Map.hpp"
#include "Player.hpp"

class MainScene final : public IScene
{
public:
	MainScene(ResourceAllocator<Texture>& textureAllocator) noexcept;
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
	ResourceAllocator<Texture>& m_textureAllocator;
	ObjectCollection			m_objectCollection;
	//std::shared_ptr<Player>		m_player;
	//std::shared_ptr<Map>		m_map;

	bool	m_isInside;
	RECT	m_addRect;
};