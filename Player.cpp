#include "DXUT.h"
#include "Player.hpp"

#include "InputManager.hpp"

extern D3DXMATRIX                  g_matrix;

Player::Player() noexcept :
	m_position(0.0f, 0.0f),
	m_direction(0.0f, 0.0f),
	m_speed(5.0f)
{
	auto device = DXUTGetD3D9Device();

	D3DXCreateLine(device, &m_line);


	m_vertexList[0] = D3DXVECTOR2( 0.5f,  0.5f);
	m_vertexList[1] = D3DXVECTOR2( 0.5f, -0.5f);
	m_vertexList[2] = D3DXVECTOR2(-0.5f, -0.5f);
	m_vertexList[3] = D3DXVECTOR2(-0.5f,  0.5f);
	m_vertexList[4] = D3DXVECTOR2( 0.5f,  0.5f);
}

Player::~Player()
{
	SAFE_RELEASE(m_line);
}

void Player::OnUpdate(float fElapsedTime)
{
	// ------- Player Control -------
	m_direction = D3DXVECTOR2(0.0f, 0.0f);
	if (g_inputManager->GetKeyPush(DIK_LEFT) == true) {
		m_direction = D3DXVECTOR2(1.0f, 0.0f);
	}
	if (g_inputManager->GetKeyPush(DIK_RIGHT) == true) {
		m_direction = D3DXVECTOR2(-1.0f, 0.0f);
	}
	if (g_inputManager->GetKeyPush(DIK_UP) == true) {
		m_direction = D3DXVECTOR2(0.0f, 1.0f);
	}
	if (g_inputManager->GetKeyPush(DIK_DOWN) == true) {
		m_direction = D3DXVECTOR2(0.0f, -1.0f);
	}
	// ------------------------------

	//m_position += m_direction * fElapsedTime;
}

void Player::OnLateUpdate(float fElapsedTime)
{
	for (UINT index = 0; index < std::size(m_vertexList); index++) {
		m_vertexList[index] += (m_position + (m_direction * m_speed * fElapsedTime));
	}
}

void Player::OnRender(float fElapsedTime)
{
	m_line->Begin();
	m_line->Draw(m_vertexList, std::size(m_vertexList), D3DCOLOR_XRGB(255, 0, 0));
	//m_line->DrawTransform(m_vertexList.data(), m_vertexList.size(), &g_matrix, D3DCOLOR_XRGB(128, 128, 128));
	m_line->End();
}

void Player::OnResetDevice()
{
	m_line->OnResetDevice();
}

void Player::OnLostDevice()
{
	m_line->OnLostDevice();
}