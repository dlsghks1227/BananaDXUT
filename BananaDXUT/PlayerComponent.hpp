#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "InputManager.hpp"

#include "Object.hpp"
#include "Component.hpp"

#include "ItemComponent.hpp"

enum class ItemType : int;
enum class PlayerDirection : int {
	None = 0,
	Left,
	Right,
	Up,
	Down
};

struct ActiveItem {
	ActiveItem(float duration) : m_activeTime(0.0f), m_activeDuration(duration), m_activedItem(false) {}

	float		m_activeTime;
	float		m_activeDuration;
	bool		m_activedItem;
};

class PlayerComponent : public Component
{
public:
	PlayerComponent(Object* owner) noexcept;
	~PlayerComponent();

	void						OnUpdate(float fElapsedTime) override;
	void						OnLateUpdate(float fElapsedTime) override;

	void						GetItem(ItemType const& type, float activeDuration);

	bool const&					IsRotated()		{ return m_isRotated; }
	PlayerDirection const&		GetDirection()	{ return m_direction; }

	D3DXVECTOR3	const&			GetVelocity()	{ return m_velocity; }
	void						Reset(D3DXVECTOR3 const& pos);

	void						IncreaseHp(int const& amount = 1);
	void						DecreaseHp(int const& amount = 1);
	int const&					GetHp()			{ return m_hp; }

private:
	D3DXVECTOR3			m_velocity;
	PlayerDirection		m_direction;

	float				m_speed;
	bool				m_isRotated;

	int					m_hp;

	std::map<ItemType, ActiveItem>		m_activeItems;

	float temp = 0.0f;
};