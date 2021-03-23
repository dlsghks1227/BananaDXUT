#include "DXUT.h"
#include "PlayerComponent.hpp"

PlayerComponent::PlayerComponent(Object* owner) noexcept 
	: Component(owner), 
	m_velocity(0.0f, 0.0f, 0.0f),
	m_direction(PlayerDirection::None),
	m_speed(100.0f), 
	m_isRotated(false)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::OnUpdate(float fElapsedTime)
{
	m_isRotated = false;
	//m_direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (g_inputManager->GetKeyPressed(DIK_LEFT) == true &&
		m_direction != PlayerDirection::Left &&
		m_direction != PlayerDirection::Right) 
	{
		m_velocity = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		m_direction = PlayerDirection::Left;
		m_isRotated = true;
	}

	if (g_inputManager->GetKeyPressed(DIK_RIGHT) == true &&
		m_direction != PlayerDirection::Right &&
		m_direction != PlayerDirection::Left) 
	{
		m_velocity = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_direction = PlayerDirection::Right;
		m_isRotated = true;
	}

	if (g_inputManager->GetKeyPressed(DIK_UP) == true &&
		m_direction != PlayerDirection::Up &&
		m_direction != PlayerDirection::Down) 
	{
		m_velocity = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		m_direction = PlayerDirection::Up;
		m_isRotated = true;
	}

	if (g_inputManager->GetKeyPressed(DIK_DOWN) == true && 
		m_direction != PlayerDirection::Down &&
		m_direction != PlayerDirection::Up) 
	{
		m_velocity = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_direction = PlayerDirection::Down;
		m_isRotated = true;
	}

	m_object->m_transform->AddPosition((m_velocity * m_speed * fElapsedTime));
}

void PlayerComponent::OnLateUpdate(float fElapsedTime)
{
}
