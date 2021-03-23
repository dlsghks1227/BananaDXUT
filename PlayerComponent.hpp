#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "InputManager.hpp"

#include "Object.hpp"
#include "Component.hpp"

enum class PlayerDirection : int {
	None = 0,
	Left,
	Right,
	Up,
	Down
};

class PlayerComponent : public Component
{
public:
	PlayerComponent(Object* owner) noexcept;
	~PlayerComponent();

	void						OnUpdate(float fElapsedTime) override;
	void						OnLateUpdate(float fElapsedTime) override;

	bool const&					IsRotated()		{ return m_isRotated; }
	PlayerDirection const&		GetDirection()	{ return m_direction; }

private:
	D3DXVECTOR3			m_velocity;
	PlayerDirection		m_direction;
	float				m_speed;
	bool				m_isRotated;
};