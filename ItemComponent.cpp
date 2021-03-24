#include "DXUT.h"
#include "ItemComponent.hpp"

ItemComponent::ItemComponent(Object* owner) noexcept
	: Component(owner),
	m_player(nullptr),
	m_type(ItemType::None),
	m_activeDuration(0.0f)
{
}

ItemComponent::~ItemComponent()
{
}

void ItemComponent::Initialize(Object* player, ItemType const& type, float activeDuration)
{
	m_player = player;

	m_type = type;
	m_activeDuration = activeDuration;
}

void ItemComponent::OnUpdate(float fElapsedTime)
{
	if (m_player != nullptr) {
		if (Collision::BoundingBoxCollision(m_object->m_transform->GetPlane(), m_player->m_transform->GetPlane()))
		{
			auto playerComponent = m_player->GetComponent<PlayerComponent>();

			playerComponent->GetItem(m_type, m_activeDuration);
			m_object->QueueForRemoval();
		}
	}
}

void ItemComponent::OnLateUpdate(float fElapsedTIme)
{
}