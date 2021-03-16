#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "IObject.hpp"
#include "texture.h"

#include "DrawRect.hpp"

class Player final : public IObject
{
public:
	Player() noexcept;
	~Player();

	Player(Player&&) = default;
	Player& operator = (Player&&) = default;

	Player(Player const&) = delete;
	Player& operator = (Player const&) = delete;

	void		OnUpdate(float fElapsedTime)		 override;
	void		OnLateUpdate(float fElapsedTime)	 override;

	void		OnRender(float fElapsedTime)		 override;

	D3DXPLANE	GetPlane() {
		return D3DXPLANE(
			m_plane.a + m_position.x,
			m_plane.b + m_position.y,
			m_plane.c + m_position.x,
			m_plane.d + m_position.y
		);
	}
	D3DXVECTOR3	GetPosition() {
		return m_position;
	}

	bool		isTurned() { return m_isTurned; }
private:
	std::shared_ptr<DrawRect>	m_drawRect;
	std::shared_ptr<Texture>	m_texture;

	D3DXPLANE					m_plane;
	D3DXVECTOR3					m_position;
	D3DXVECTOR3					m_direction;
	float						m_speed;
	bool						m_isTurned;
};