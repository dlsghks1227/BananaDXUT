#include "DXUT.h"
#include "EnemyComponent.hpp"

EnemyComponent::EnemyComponent(Object* owner) noexcept
	: Component(owner),
	m_player(nullptr),
	m_stage(nullptr),
	m_velocity(0.0f, 0.0f, 0.0f),
	m_angle(45.0f),
	m_isCollided(false)
{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize(Object* player, Object* stage)
{
	m_player = player;
	m_stage = stage;
}

void EnemyComponent::OnUpdate(float fElapsedTime)
{
	if (m_player != nullptr && m_stage != nullptr) {
		auto stageComponent = m_stage->GetComponent<StageComponent>();
		MapInfo currentMapInfo = stageComponent->GetMapInfoInPosition(m_object->m_transform->GetPosition());
		bool isCollided = currentMapInfo == MapInfo::Paint;
		if (m_isCollided != isCollided) {
			m_isCollided = isCollided;

			if (m_isCollided == true) {
				m_angle += 90.0f;
			}
		}
	}
	m_velocity = D3DXVECTOR3(
		std::cos(D3DXToRadian(m_angle)),
		std::sin(D3DXToRadian(m_angle)),
		0.0f);
}

void EnemyComponent::OnLateUpdate(float fElapsedTIme)
{
	m_object->m_transform->AddPosition(m_velocity * 50.0f * fElapsedTIme);
}
