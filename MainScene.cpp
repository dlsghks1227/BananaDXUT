#include "DXUT.h"
#include "MainScene.hpp"

#include "Collision.hpp"

extern CDXUTDialogResourceManager	g_dialogResourceManager;

MainScene::MainScene(ResourceAllocator<Texture>& textureAllocator) noexcept :
	m_player(nullptr),
	m_stage(nullptr),
	m_textureAllocator(textureAllocator)
{
}

MainScene::~MainScene()
{
	m_objectCollection.reset();
}

void MainScene::OnEnterScene()
{
	m_HUD.Init(&g_dialogResourceManager);
	m_UI.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_UI.SetCallback(OnGUIEvent);

	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_TOGGLEFULLSCREEN), L"Toggle full screen", 35, 10, 125, 22);

	m_UI.SetFont(1, L"Comic Sans MS", 48, FW_NORMAL);
	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT), L"TEST", 300, 300, 620, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->iFont = 1;

	m_objectCollection = std::make_shared<ObjectCollection>();

	// ---------- Background ----------
	std::shared_ptr<Object>		background = std::make_shared<Object>();

	auto backgroundSprite = background->AddComponent<Sprite>();
	backgroundSprite->SetTextureAllocator(&m_textureAllocator);
	backgroundSprite->LoadTexture(L"Res/background.png");

	background->m_transform->SetPosition(0.0f, 0.0f, 1.0f);
	background->m_transform->SetCenter();

	m_objectCollection->Add(background);
	// --------------------------------

	// ---------- Player ----------
	std::shared_ptr<Object>		player = std::make_shared<Object>();
	m_player = player.get();

	auto playerSprite = player->AddComponent<Sprite>();
	playerSprite->SetTextureAllocator(&m_textureAllocator);
	playerSprite->LoadTexture(L"Res/player.png");

	auto playerComponent = player->AddComponent<PlayerComponent>();

	player->m_transform->SetScale(0.1f, 0.1f);
	player->m_transform->SetPosition(300.0f, 0.0f, 0.0f);
	player->m_transform->SetAngle(45.0f);
	player->m_transform->SetCenter();
	// ----------------------------

	// ---------- Stage ----------
	std::shared_ptr<Object>		stage = std::make_shared<Object>();
	m_stage = stage.get();
	auto stageComponent = stage->AddComponent<StageComponent>();
	stageComponent->Initialize(player.get(), m_objectCollection.get(), &m_textureAllocator, L"Res/Map.jpg");
	// ---------------------------

	// ---------- Enemy ----------
	std::shared_ptr<Object>		enemy = std::make_shared<Object>();
	auto enemyComponent = enemy->AddComponent<EnemyComponent>();
	enemyComponent->Initialize(player.get(), stage.get(), m_objectCollection.get(), &m_textureAllocator);

	auto enemySprite = enemy->AddComponent<Sprite>();
	enemySprite->SetTextureAllocator(&m_textureAllocator);
	enemySprite->LoadTexture(L"Res/enemy.png");

	enemy->m_transform->SetScale(0.2f, 0.2f);
	enemy->m_transform->SetPosition(100.0f, 200.0f, 0.0f);
	enemy->m_transform->SetCenter();

	// Debug
	enemy->AddComponent<DrawRect>();
	// ---------------------------

	m_objectCollection->Add(player);
	m_objectCollection->Add(stage);
	m_objectCollection->Add(enemy);
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
	if (m_player != nullptr && m_stage != nullptr)
	{
		auto playerComponent = m_player->AddComponent<PlayerComponent>();

		std::wstringstream playerHpString(L"");
		playerHpString << L"HP: " << playerComponent->GetHp();
		m_UI.GetStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->SetText(playerHpString.str().c_str());

	}
	m_objectCollection->OnLateUpdate(fElapsedTime);
}

void MainScene::OnRender(float fElapsedTime)
{
	m_objectCollection->OnRender(fElapsedTime);
}

void MainScene::OnUIRender(float fElapsedTime)
{
	m_HUD.OnRender(fElapsedTime);
	m_UI.OnRender(fElapsedTime);
}

void MainScene::OnResetDevice()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation(backBufferSurfaceDesc->Width - 170, 0);
	m_HUD.SetSize(170, 170);

	m_UI.SetLocation(0, 0);
	m_UI.SetSize(backBufferSurfaceDesc->Width, backBufferSurfaceDesc->Height);
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
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	*pbNoFurtherProcessing = m_UI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}