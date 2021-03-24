#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Collision.hpp"

#include "Object.hpp"
#include "Component.hpp"

#include "PlayerComponent.hpp"

enum class ItemType : int {
	None = 0,
	SpeedUp,
	SpeedDown
};

class ItemComponent : public Component
{
public:
	ItemComponent(Object* owner) noexcept;
	~ItemComponent();

	void		Initialize(Object* player, ItemType const& type, float activeDuration);

	void		OnUpdate(float fElapsedTime)		override;
	void		OnLateUpdate(float fElapsedTIme)	override;

private:
	Object*		m_player;

	ItemType	m_type;
	float		m_activeDuration;
};

