#include "DXUT.h"
#include "MainScene.hpp"

#include "Collision.hpp"

MainScene::MainScene(ResourceAllocator<Texture>& textureAllocator) noexcept :
	m_textureAllocator(textureAllocator)
{
}

MainScene::~MainScene()
{
	m_objectCollection.reset();
}

void MainScene::OnEnterScene()
{
	m_objectCollection = std::make_shared<ObjectCollection>();

	std::shared_ptr<Object>		player = std::make_shared<Object>();

	auto playerSprite = player->AddComponent<Sprite>();
	playerSprite->SetTextureAllocator(&m_textureAllocator);
	playerSprite->LoadTexture(L"Res/Player/default.png");

	auto movenent = player->AddComponent<PlayerComponent>();
	player->m_transform->SetScale(0.05f, 0.05f);
	player->m_transform->SetCenter();
	player->m_transform->SetPosition(300.0f, 0.0f, 0.0f);

	player->AddComponent<DrawRect>();


	std::shared_ptr<Object>		stage = std::make_shared<Object>();
	auto stageComponent = stage->AddComponent<StageComponent>();
	stageComponent->Initialize(player.get(), m_objectCollection.get(), &m_textureAllocator, L"Res/Map.jpg");

	stage->AddComponent<DrawRect>();

	m_objectCollection->Add(player);
	m_objectCollection->Add(stage);
}

void MainScene::OnExitScene()
{
	m_objectCollection.reset();
}

void MainScene::OnUpdate(float fElapsedTime)
{
	m_objectCollection->ProcessRemovals();
	m_objectCollection->ProcessNewObjects();

	m_objectCollection->OnUpdate(fElapsedTime);
}

void MainScene::OnLateUpdate(float fElapsedTime)
{
	m_objectCollection->OnLateUpdate(fElapsedTime);

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
	m_objectCollection->OnRender(fElapsedTime);
}

void MainScene::OnResetDevice()
{
}

void MainScene::OnLostDevice()
{
}

void MainScene::OnDestroyDevice()
{
	m_objectCollection.reset();
}

LRESULT MainScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return 0;
}