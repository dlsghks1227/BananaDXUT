#include "DXUT.h"
#include "ItemComponent.hpp"

ItemComponent::ItemComponent(Object* owner) noexcept
	: Component(owner)
{
}

ItemComponent::~ItemComponent()
{
}

void ItemComponent::Initialize(Object* player)
{
}

void ItemComponent::OnUpdate(float fElapsedTime)
{
}

void ItemComponent::OnLateUpdate(float fElapsedTIme)
{
}