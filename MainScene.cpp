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

	// ---------- Player ----------
	std::shared_ptr<Object>		player = std::make_shared<Object>();

	auto playerSprite = player->AddComponent<Sprite>();
	playerSprite->SetTextureAllocator(&m_textureAllocator);
	playerSprite->LoadTexture(L"Res/Player/default.png");

	auto movenent = player->AddComponent<PlayerComponent>();

	player->m_transform->SetScale(0.05f, 0.05f);
	player->m_transform->SetPosition(300.0f, 0.0f, 0.0f);
	player->m_transform->SetCenter();

	// Debug
	player->AddComponent<DrawRect>();
	// ----------------------------

	// ---------- Stage ----------
	std::shared_ptr<Object>		stage = std::make_shared<Object>();
	auto stageComponent = stage->AddComponent<StageComponent>();
	stageComponent->Initialize(player.get(), m_objectCollection.get(), &m_textureAllocator, L"Res/Map.jpg");

	// Debug
	stage->AddComponent<DrawRect>();
	// ---------------------------

	// ---------- Enemy ----------
	std::shared_ptr<Object>		enemy = std::make_shared<Object>();
	auto enemyComponent = enemy->AddComponent<EnemyComponent>();
	enemyComponent->Initialize(player.get(), stage.get());

	auto enemySprite = enemy->AddComponent<Sprite>();
	enemySprite->SetTextureAllocator(&m_textureAllocator);
	enemySprite->LoadTexture(L"Res/Player/default.png");

	enemy->m_transform->SetScale(0.05f, 0.05f);
	enemy->m_transform->SetPosition(0.0f, 0.0f, 0.0f);
	enemy->m_transform->SetCenter();

	// Debug
	enemy->AddComponent<DrawRect>();
	// ---------------------------

	// ---------- Item ----------
	std::shared_ptr<Object>		item = std::make_shared<Object>();
	auto itemComponent = item->AddComponent<ItemComponent>();
	itemComponent->Initialize(player.get(), ItemType::SpeedUp, 4.0f);

	item->m_transform->SetRect(0, 0, 50, 50);
	item->m_transform->SetPosition(0.0f, 0.0f, 100.0f);
	item->m_transform->SetCenter();

	// Debug
	item->AddComponent<DrawRect>();
	// ---------------------------

		// ---------- Item ----------
	std::shared_ptr<Object>		item2 = std::make_shared<Object>();
	auto item2Component = item2->AddComponent<ItemComponent>();
	item2Component->Initialize(player.get(), ItemType::SpeedDown, 3.0f);

	item2->m_transform->SetRect(0, 0, 50, 50);
	item2->m_transform->SetPosition(100.0f, 100.0f, 100.0f);
	item2->m_transform->SetCenter();

	// Debug
	item2->AddComponent<DrawRect>();
	// ---------------------------

	m_objectCollection->Add(player);
	m_objectCollection->Add(stage);
	m_objectCollection->Add(enemy);
	m_objectCollection->Add(item);
	m_objectCollection->Add(item2);
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