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

	D3DXVECTOR2	GetMapSize() {
		return m_mapSize;
	}

private:
	std::shared_ptr<DrawRect>	m_drawRect;
	std::shared_ptr<Texture>	m_texture;
	std::vector<RECT>			m_mapRects;

	D3DXVECTOR2					m_mapSize;
};