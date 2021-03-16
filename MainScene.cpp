#include "DXUT.h"
#include "MainScene.h"

#include "Collision.h"

MainScene::MainScene() noexcept :
	m_isInside(false),
	m_addRect{0, 0, 0, 0}
{
}

MainScene::~MainScene()
{
	m_map.reset();
	m_player.reset();
}

void MainScene::OnEnterScene()
{
	m_map = std::make_unique<Map>();
	m_player = std::make_unique<Player>();
}

void MainScene::OnExitScene()
{
	m_map.reset();
	m_player.reset();
}

void MainScene::OnUpdate(float fElapsedTime)
{
	m_map->OnUpdate(fElapsedTime);
	m_player->OnUpdate(fElapsedTime);
}

void MainScene::OnLateUpdate(float fElapsedTime)
{
	m_map->OnLateUpdate(fElapsedTime);
	m_player->OnLateUpdate(fElapsedTime);

	bool isCollision = Collision::BoundingBoxPointCollision(m_map->GetPlane(), m_player->GetPosition());
	if (m_isInside != isCollision) {
		m_isInside = isCollision;

		if (m_isInside == true) {
			// µé¾î°¬À» ¶§
			m_addRect.left = static_cast<int>(std::round((m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x));
			m_addRect.top = static_cast<int>(std::round((m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y));
			std::cout << (m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x << '\n';
			std::cout << (m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y << '\n';
		}
		else {
			// ³ª°¬À» ¶§
			m_addRect.right = static_cast<int>(std::round((m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x));
			m_addRect.bottom = static_cast<int>(std::round((m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y));
			std::cout << (m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x << '\n';
			std::cout << (m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y << '\n';
			m_map->AddMap(m_addRect);
			m_addRect = { 0, 0, 0, 0 };
		}
	}
	//bool isCollision = Collision::BoundingBoxCollision(m_map->GetPlane(), m_player->GetPlane());
}

void MainScene::OnRender(float fElapsedTime)
{
	m_map->OnRender(fElapsedTime);
	m_player->OnRender(fElapsedTime);
}

void MainScene::OnResetDevice()
{
}

void MainScene::OnLostDevice()
{
}

void MainScene::OnDestroyDevice()
{
	m_map.reset();
	m_player.reset();
}

LRESULT MainScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return 0;
}
