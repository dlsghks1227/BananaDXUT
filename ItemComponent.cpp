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

void ItemComponent::Initialize(Object* player, ItemType const& type, float activeDuration, ResourceAllocator<Texture>* textureAllocator)
{
	m_player = player;

	m_type = type;
	m_activeDuration = activeDuration;

	auto sprite = m_object->AddComponent<Sprite>();
	switch (m_type) {
	case ItemType::SpeedUp:
		sprite->SetTextureAllocator(textureAllocator);
		sprite->LoadTexture(L"Res/item_SpeedUp.png");
		break;
	case ItemType::HpUp:
		sprite->SetTextureAllocator(textureAllocator);
		sprite->LoadTexture(L"Res/item_HpUp.png");
		break;
	}
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