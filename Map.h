#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "IObject.hpp"
#include "Texture.h"

#include "DrawRect.hpp"

class Map : public IObject
{
public:
	Map() noexcept;
	~Map();

	Map(Map&&) = default;
	Map& operator = (Map&&) = default;

	Map(Map const&) = delete;
	Map& operator = (Map const&) = delete;

	void		OnUpdate(float fElapsedTime)		override;
	void		OnLateUpdate(float fElapsedTime)	override;

	void		OnRender(float fElapsedTime)		override;

	void		AddMap(RECT rect) {
		m_mapRects.push_back(rect);
		std::wcout << "Add Rect\n";
	}

	D3DXPLANE	GetPlane() {
		return D3DXPLANE(
			m_plane.a + m_position.x,
			m_plane.b + m_position.y,
			m_plane.c + m_position.x,
			m_plane.d + m_position.y
		);
	}
	D3DXVECTOR2	GetMapSize() {
		return m_mapSize;
	}
	D3DXVECTOR3	GetPosition() {
		return m_position;
	}

private:
	std::shared_ptr<DrawRect>	m_drawRect;
	std::shared_ptr<Texture>	m_texture;
	std::vector<RECT>			m_mapRects;

	D3DXPLANE					m_plane;
	D3DXVECTOR3					m_position;
	D3DXVECTOR2					m_mapSize;
};