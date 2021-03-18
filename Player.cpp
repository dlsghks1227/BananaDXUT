#include "DXUT.h"
#include "Player.hpp"

#include "InputManager.hpp"

extern D3DXMATRIXA16               g_matrix;

Player::Player() noexcept :
	m_direction(0.0f, 0.0f, 0.0f),
	m_speed(200.0f),
	m_isTurned(false)
{
	m_drawRect = std::make_shared<DrawRect>();
	m_drawRect->SetColor(D3DCOLOR_XRGB(255, 0, 0));

	m_plane = D3DXPLANE(-50.0f, -50.0f, 50.0f, 50.0f);

	m_texture = std::make_shared<Texture>();
	m_texture->LoadFromFile(L"Res/Player/default.png");
}

Player::~Player()
{
	m_drawRect.reset();
	m_texture.reset();
}

void Player::OnUpdate(float fElapsedTime)
{
	// ------- Player Control -------
	m_direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_isTurned = false;
	if (g_inputManager->GetKeyPush(DIK_LEFT) == true) {
		m_direction = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		m_isTurned = true;
	}
	if (g_inputManager->GetKeyPush(DIK_RIGHT) == true) {
		m_direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_isTurned = true;
	}
	if (g_inputManager->GetKeyPush(DIK_UP) == true) {
		m_direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		m_isTurned = true;
	}
	if (g_inputManager->GetKeyPush(DIK_DOWN) == true) {
		m_direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_isTurned = true;
	}
	m_transform->AddPosition((m_direction * m_speed * fElapsedTime));
	// ------------------------------

	m_drawRect->SetPlane(this->GetPlane());
	m_drawRect->OnUpdate(fElapsedTime);
}

void Player::OnLateUpdate(float fElapsedTime)
{
}

void Player::OnRender(float fElapsedTime)
{
	m_texture->SetScale(D3DXVECTOR2(0.1f, 0.1f));
	m_texture->SetPosition(m_transform->GetPosition());
	m_texture->Draw();

	m_drawRect->OnRender(fElapsedTime);
}