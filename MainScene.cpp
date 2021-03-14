#include "DXUT.h"
#include "MainScene.h"

MainScene::MainScene() noexcept
{
}

MainScene::~MainScene()
{
	m_player.reset();
}

void MainScene::OnEnterScene()
{
	m_player = std::make_unique<Player>();
}

void MainScene::OnExitScene()
{
	m_player.reset();
}

void MainScene::OnUpdate(float fElapsedTime)
{
	if (m_player) {
		m_player->OnUpdate(fElapsedTime);
	}
}

void MainScene::OnLateUpdate(float fElapsedTime)
{
	if (m_player) {
		m_player->OnLateUpdate(fElapsedTime);
	}
}

void MainScene::OnRender(float fElapsedTime)
{
	if (m_player) {
		m_player->OnRender(fElapsedTime);
	}
}

void MainScene::OnResetDevice()
{
	if (m_player) {
		m_player->OnResetDevice();
	}
}

void MainScene::OnLostDevice()
{
	if (m_player) {
		m_player->OnLostDevice();
	}
}

void MainScene::OnDestroyDevice()
{
	m_player.reset();
}

LRESULT MainScene::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	return 0;
}
