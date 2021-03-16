#pragma once
#include "DXUT.h"
#include "header.hpp"

extern D3DXMATRIXA16		g_matrix;
extern LPD3DXLINE			g_pLine;

class DrawRect final
{
public:
	DrawRect() noexcept : 
		m_plane(0.0f, 0.0f, 0.0f, 0.0f),
		m_color(D3DCOLOR_XRGB(255, 255, 255))
	{
	}
	~DrawRect() = default;

	DrawRect(DrawRect&&) = default;
	DrawRect& operator = (DrawRect&&) = default;

	DrawRect(DrawRect const&) = delete;
	DrawRect& operator = (DrawRect const&) = delete;

	void	OnUpdate(float fElapsedTime) {
		m_vertexList[0] = D3DXVECTOR3(m_plane.a,	m_plane.b,	-0.1f);
		m_vertexList[1] = D3DXVECTOR3(m_plane.c,	m_plane.b,	-0.1f);
		m_vertexList[2] = D3DXVECTOR3(m_plane.c,	m_plane.d,	-0.1f);
		m_vertexList[3] = D3DXVECTOR3(m_plane.a,	m_plane.d,	-0.1f);
		m_vertexList[4] = D3DXVECTOR3(m_plane.a,	m_plane.b,	-0.1f);
	}

	void	OnRender(float fElapsedTime) {
		g_pLine->DrawTransform(m_vertexList, std::size(m_vertexList), &g_matrix, m_color);
	}

	void			SetColor(D3DXCOLOR const& color) {
		m_color = color;
	}
	void			SetPlane(D3DXPLANE const& plane) {
		m_plane = plane;
	}

private:
	D3DXPLANE		m_plane;
	D3DXCOLOR		m_color;

	D3DXVECTOR3		m_vertexList[5];
};