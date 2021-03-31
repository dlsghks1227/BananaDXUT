#include "DXUT.h"
#include "Stage2Scene.hpp"

#include "Collision.hpp"

extern CDXUTDialogResourceManager	g_dialogResourceManager;

Stage2Scene::Stage2Scene(
	ResourceAllocator<Texture>& textureAllocator,
	SceneStateMachine& sceneStateMachine
) noexcept :
	m_player(nullptr),
	m_stage(nullptr),
	m_textureAllocator(textureAllocator),
	m_sceneStateMachine(sceneStateMachine)
{
	m_HUD.Init(&g_dialogResourceManager);
	m_UI.Init(&g_dialogResourceManager);

	m_HUD.SetCallback(OnGUIEvent);
	m_UI.SetCallback(OnGUIEvent);

	m_HUD.SetFont(0, L"Comic Sans MS", 24, FW_NORMAL);
	m_HUD.AddButton(static_cast<int>(UI_CONTROL_ID::IDC_MENU_BUTTON), L"Menu", 0, 0, 200, 30);

	m_UI.SetFont(1, L"Comic Sans MS", 48, FW_NORMAL);
	m_UI.SetFont(2, L"Comic Sans MS", 100, FW_NORMAL);
	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT), L"", 20, 20, 620, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->GetElement(0)->iFont = 1;

	m_UI.AddStatic(static_cast<int>(UI_CONTROL_ID::IDC_CLEAR_TEXT), L"", 20, 100, 300, 300);
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_CLEAR_TEXT))->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_CLEAR_TEXT))->GetElement(0)->iFont = 2;
}

Stage2Scene::~Stage2Scene()
{
	m_objectCollection.reset();
}

void Stage2Scene::OnEnterScene()
{
	auto backBufferSurfaceDesc = DXUTGetD3D9BackBufferSurfaceDesc();

	m_HUD.SetLocation(backBufferSurfaceDesc->Width - 220, 20);
	m_HUD.SetSize(200, 300);

	m_UI.SetLocation(0, 0);
	m_UI.SetSize(backBufferSurfaceDesc->Width, backBufferSurfaceDesc->Height);

	m_UI.GetControl(static_cast<int>(UI_CONTROL_ID::IDC_CLEAR_TEXT))->SetLocation(
		backBufferSurfaceDesc->Width / 2 - 150,
		backBufferSurfaceDesc->Height / 2 - 150
	);

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
	player->m_transform->SetPosition(600.0f, 0.0f, 0.0f);
	player->m_transform->SetAngle(45.0f);
	player->m_transform->SetCenter();

	m_objectCollection->Add(player);
	// ----------------------------

	// ---------- Stage ----------
	std::shared_ptr<Object>		stage = std::make_shared<Object>();
	m_stage = stage.get();
	auto stageComponent = stage->AddComponent<StageComponent>();
	stageComponent->Initialize(player.get(), m_objectCollection.get(), &m_textureAllocator, L"Res/background2.jpg");

	m_objectCollection->Add(stage);
	// ---------------------------

	// ---------- Enemy ----------
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Object>		enemy = std::make_shared<Object>();
		auto enemyComponent = enemy->AddComponent<EnemyComponent>();
		enemyComponent->Initialize(150.0f, player.get(), stage.get(), m_objectCollection.get(), &m_textureAllocator);

		auto enemySprite = enemy->AddComponent<Sprite>();
		enemySprite->SetTextureAllocator(&m_textureAllocator);
		enemySprite->LoadTexture(L"Res/enemy.png");


		std::random_device rng;
		std::uniform_int_distribution<int>	widthDist(20, stageComponent->GetMapWidth() - 20);
		std::uniform_int_distribution<int>	heightDist(20, stageComponent->GetMapHeight() - 20);
		POINT enemyPoint = {
			widthDist(rng),
			heightDist(rng)
		};
		D3DXVECTOR2	enemyPos = stageComponent->GetWorldPosition(enemyPoint);

		enemy->m_transform->SetScale(0.2f, 0.2f);
		enemy->m_transform->SetPosition(enemyPos.x, enemyPos.y, 0.0f);
		enemy->m_transform->SetCenter();

		m_objectCollection->Add(enemy);
	}
	// ---------------------------


	// ---------- Boss ----------
	std::shared_ptr<Object>		boss = std::make_shared<Object>();
	auto bossComponent = boss->AddComponent<EnemyComponent>();
	bossComponent->Initialize(100.0f, player.get(), stage.get(), m_objectCollection.get(), &m_textureAllocator);

	auto bossSprite = boss->AddComponent<Sprite>();
	bossSprite->SetTextureAllocator(&m_textureAllocator);
	bossSprite->LoadTexture(L"Res/boss.png");

	boss->m_transform->SetScale(0.6f, 0.6f);
	boss->m_transform->SetPosition(0.0f, 0.0f, 0.0f);
	boss->m_transform->SetCenter();

	m_objectCollection->Add(boss);
	// --------------------------

}

void Stage2Scene::OnExitScene()
{
	m_objectCollection.reset();
}

void Stage2Scene::OnUpdate(float fElapsedTime)
{
	m_objectCollection->ProcessRemovals();
	m_objectCollection->ProcessNewObjects();

	m_objectCollection->OnUpdate(fElapsedTime);
}

void Stage2Scene::OnLateUpdate(float fElapsedTime)
{
	m_objectCollection->OnLateUpdate(fElapsedTime);

	if (m_player != nullptr && m_stage != nullptr)
	{
		auto playerComponent = m_player->AddComponent<PlayerComponent>();

		std::wstringstream playerHpString(L"");
		playerHpString << L"Stage 2\n" << L"HP: " << playerComponent->GetHp();
		m_UI.GetStatic(static_cast<int>(UI_CONTROL_ID::IDC_HP_TEXT))->SetText(playerHpString.str().c_str());


		auto stageComponent = m_stage->AddComponent<StageComponent>();

		std::wstringstream claerMapString(L"");
		claerMapString << std::fixed;
		claerMapString.precision(1);
		claerMapString << stageComponent->GetClearMap() * 100.0f << " %";
		m_UI.GetStatic(static_cast<int>(UI_CONTROL_ID::IDC_CLEAR_TEXT))->SetText(claerMapString.str().c_str());

		if (playerComponent->GetHp() <= 0) {
			m_sceneStateMachine.SwitchTo(L"GameOverScene");
		}

		if (stageComponent->GetClearMap() > 0.8f) {
			m_sceneStateMachine.SwitchTo(L"GameClearScene");
		}
	}
}

void Stage2Scene::OnRender(float fElapsedTime)
{
	m_objectCollection->OnRender(fElapsedTime);
}

void Stage2Scene::OnUIRender(float fElapsedTime)
{
	m_HUD.OnRender(fElapsedTime);
	m_UI.OnRender(fElapsedTime);
}

void Stage2Scene::OnResetDevice()
{
}

void Stage2Scene::OnLostDevice()
{
}

void Stage2Scene::OnDestroyDevice()
{
	m_objectCollection.reset();
}

LRESULT Stage2Scene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	*pbNoFurtherProcessing = m_HUD.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	*pbNoFurtherProcessing = m_UI.MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}