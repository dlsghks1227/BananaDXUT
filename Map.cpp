#include "DXUT.h"
#include "Map.hpp"


Map::Map() noexcept
{
	m_texture = std::make_shared<Texture>(L"Res/background.jpg");
	m_mapSize = D3DXVECTOR2(
		static_cast<float>(m_texture->GetWidth()),
		static_cast<float>(m_texture->GetHeight()));
	m_plane = D3DXPLANE(
		m_mapSize.x * -0.5f,
		m_mapSize.y * -0.5f,
		m_mapSize.x *  0.5f,
		m_mapSize.y *  0.5f
	);

	m_drawRect = std::make_shared<DrawRect>();
	m_drawRect->SetColor(D3DCOLOR_XRGB(0, 255, 0));
}

Map::~Map()
{
	m_drawRect.reset();
	m_texture.reset();
}

void Map::OnUpdate(float fElapsedTime)
{
	m_drawRect->SetPlane(this->GetPlane());
	m_drawRect->OnUpdate(fElapsedTime);
}

void Map::OnLateUpdate(float fElapsedTime)
{
}

void Map::OnRender(float fElapsedTime)
{
	for (auto& rect : m_mapRects) {
		m_texture->SetPosition(D3DXVECTOR3(float(rect.left) - (m_mapSize.x / 2.0f), float(rect.top) - (m_mapSize.y / 2.0f), 0.0f));
		m_texture->Draw(&rect, false);
	}

	m_drawRect->OnRender(fElapsedTime);
}