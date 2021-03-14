#pragma once
#include "DXUT.h"
#include "header.hpp"

class Player final
{
public:
	Player() noexcept;
	~Player();

	Player(Player&&) = default;
	Player& operator = (Player&&) = default;

	Player(Player const&) = delete;
	Player& operator = (Player const&) = delete;

	void	OnUpdate(float fElapsedTime);
	void	OnLateUpdate(float fElapsedTime);

	void	OnRender(float fElapsedTime);

	void	OnResetDevice();
	void	OnLostDevice();
private:
	D3DXVECTOR2					m_position;
	D3DXVECTOR2					m_direction;
	float						m_speed;

	LPD3DXLINE					m_line;
	D3DXVECTOR2					m_vertexList[5];
	//std::vector<D3DXVECTOR3>	m_vertexList;
};