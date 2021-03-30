#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Collision.hpp"

#include "Object.hpp"
#include "Component.hpp"

#include "StageComponent.hpp"
#include "ItemComponent.hpp"

class EnemyComponent : public Component
{
public:
	EnemyComponent(Object* owner) noexcept;
	~EnemyComponent();

	void			Initialize(
		float speed,
		Object* player,
		Object* stage,
		ObjectCollection* objectCollection,
		ResourceAllocator<Texture>* textureAllocator
	);

	void			OnUpdate(float fElapsedTime)		override;
	void			OnLateUpdate(float fElapsedTIme)	override;

	void			OnRender(float fElapsedTIme)		override;

private:
	D3DXVECTOR3		GetCollisionPosition(float const& angle);
	void			CreateItem(D3DXVECTOR2 const& pos, ItemType const& type);

	Object*						m_player;
	Object*						m_stage;
	ObjectCollection*			m_objectCollection;
	ResourceAllocator<Texture>* m_textureAllocator;


	D3DXVECTOR3			m_leftCollisionPosition;
	D3DXVECTOR3			m_rightCollisionPosition;
	D3DXVECTOR3			m_velocity;
	float				m_speed;
	float				m_angle;

	bool				m_isLeftCollided;
	bool				m_isRightCollided;
};

