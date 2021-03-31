#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "DXUTsettingsdlg.h"
#include "header.hpp"

#include "IScene.hpp"

#include "ResourceAllocator.hpp"

#include "Object.hpp"
#include "ObjectCollection.h"

#include "Transform.hpp"
#include "Sprite.hpp"

#include "PlayerComponent.hpp"
#include "StageComponent.hpp"
#include "EnemyComponent.hpp"
#include "ItemComponent.hpp"

#include "Event.hpp"

#include "SceneStateMachine.hpp"


class Stage2Scene final : public IScene
{
public:
	Stage2Scene(
		ResourceAllocator<Texture>& textureAllocator,
		SceneStateMachine& sceneStateMachine
	) noexcept;
	~Stage2Scene();

	Stage2Scene(Stage2Scene&&) = default;
	Stage2Scene& operator = (Stage2Scene&&) = default;

	Stage2Scene(Stage2Scene const&) = delete;
	Stage2Scene& operator = (Stage2Scene const&) = delete;

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

	Object* m_player;
	Object* m_stage;

	ResourceAllocator<Texture>&			m_textureAllocator;
	SceneStateMachine&					m_sceneStateMachine;
	std::shared_ptr<ObjectCollection>	m_objectCollection;
};

