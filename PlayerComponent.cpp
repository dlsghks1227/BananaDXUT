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

	//if (m_activedItem == true) {
	//	m_activeTime += fElapsedTime;

	//	if (m_activeTime)
	//}
}

void PlayerComponent::OnLateUpdate(float fElapsedTime)
{
	if (m_activeItems.empty() == false) {
		auto itr = m_activeItems.begin();
		while (itr != m_activeItems.end()) {
			itr->second.m_activeTime += fElapsedTime;

			switch (itr->first) {
			case ItemType::SpeedUp:
				m_speed = 200.0f;
				if (itr->second.m_activeTime >= itr->second.m_activeDuration) {
					m_speed = 100.0f;
					itr->second.m_activedItem = true;
				}
				break;
			case ItemType::SpeedDown:
				m_speed = 50.0f;
				if (itr->second.m_activeTime >= itr->second.m_activeDuration) {
					m_speed = 100.0f;
					itr->second.m_activedItem = true;
				}
				break;
			}

			if (itr->second.m_activedItem == true) {
				itr = m_activeItems.erase(itr);
			}
			else {
				++itr;
			}
		}
	}

	m_object->m_transform->AddPosition((m_velocity * m_speed * fElapsedTime));
}

void PlayerComponent::GetItem(ItemType const& type, float activeDuration)
{
	auto itr = m_activeItems.find(type);
	if (itr != m_activeItems.end()) {
		itr->second.m_activeTime = 0.0f;
		itr->second.m_activeDuration = activeDuration;
		itr->second.m_activedItem = false;
	}
	else {
		m_activeItems.insert(std::make_pair(type, ActiveItem(activeDuration)));
	}
}
