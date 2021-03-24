#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Collision.hpp"

#include "Object.hpp"
#include "Component.hpp"

#include "StageComponent.hpp"


class EnemyComponent : public Component
{
public:
	EnemyComponent(Object* owner) noexcept;
	~EnemyComponent();

	void			Initialize(Object* player, Object* stage);

	void			OnUpdate(float fElapsedTime)		override;
	void			OnLateUpdate(float fElapsedTIme)	override;

private:
	Object*			m_player;
	Object*			m_stage;

	D3DXVECTOR3		m_velocity;
	float			m_speed;
	float			m_angle;

	bool			m_isCollided;
};

