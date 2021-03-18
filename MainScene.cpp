#include "DXUT.h"
#include "MainScene.hpp"

#include "Collision.hpp"

MainScene::MainScene(ResourceAllocator<Texture>& textureAllocator) noexcept :
	m_textureAllocator(textureAllocator),
	m_isInside(false),
	m_addRect{0, 0, 0, 0}
{
}

MainScene::~MainScene()
{
	m_objectCollection.AllObjectRelelase();
}

void MainScene::OnEnterScene()
{
	std::shared_ptr<Object>		m_player = std::make_shared<Object>();
	auto sprite = m_player->AddComponent<Sprite>();
	sprite->SetTextureAllocator(&m_textureAllocator);
	sprite->LoadTexture(L"Res/Player/default.png");

	//std::shared_ptr<Map>		m_map = std::make_shared<Map>();


	m_objectCollection.Add(m_player);
	//m_objectCollection.Add(m_map);
}

void MainScene::OnExitScene()
{
	m_objectCollection.AllObjectRelelase();
}

void MainScene::OnUpdate(float fElapsedTime)
{
	m_objectCollection.ProcessNewObjects();

	m_objectCollection.OnUpdate(fElapsedTime);
}

void MainScene::OnLateUpdate(float fElapsedTime)
{
	m_objectCollection.OnLateUpdate(fElapsedTime);

	//bool isCollision = Collision::BoundingBoxPointCollision(m_map->GetPlane(), m_player->GetPosition());
	//if (m_isInside != isCollision) {
	//	m_isInside = isCollision;

	//	if (m_isInside == true) {
	//		// µé¾î°¬À» ¶§
	//		m_addRect.left = static_cast<int>(std::round((m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x));
	//		m_addRect.top = static_cast<int>(std::round((m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y));
	//		std::cout << (m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x << '\n';
	//		std::cout << (m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y << '\n';
	//	}
	//	else {
	//		// ³ª°¬À» ¶§
	//		m_addRect.right = static_cast<int>(std::round((m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x));
	//		m_addRect.bottom = static_cast<int>(std::round((m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y));
	//		std::cout << (m_map->GetMapSize().x * 0.5f) + m_player->GetPosition().x << '\n';
	//		std::cout << (m_map->GetMapSize().y * 0.5f) + m_player->GetPosition().y << '\n';
	//		m_map->AddMap(m_addRect);
	//		m_addRect = { 0, 0, 0, 0 };
	//	}
	//}
	//bool isCollision = Collision::BoundingBoxCollision(m_map->GetPlane(), m_player->GetPlane());
}

void MainScene::OnRender(float fElapsedTime)
{
	m_objectCollection.OnRender(fElapsedTime);
}

void MainScene::OnResetDevice()
{
}

void MainScene::OnLostDevice()
{
}

void MainScene::OnDestroyDevice()
{
	m_objectCollection.AllObjectRelelase();
}

LRESULT MainScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return 0;
}
