#pragma once
#include "DXUT.h"
#include "header.hpp"

extern D3DXMATRIXA16		g_matrix;
extern LPD3DXLINE			g_pLine;

class DrawLine
{
public:
	DrawLine() noexcept : m_color(D3DCOLOR_XRGB(255, 255, 255)), m_width(1.0f) {

	}

	DrawLine(D3DXVECTOR3 start, D3DXVECTOR3 end) noexcept : m_color(D3DCOLOR_XRGB(255, 255, 255)), m_width(1.0f) {
		m_vertexList[0] = start;
		m_vertexList[1] = end;
	}

	DrawLine(D3DXVECTOR3 const& start, D3DXVECTOR3 const& end, float width, D3DXCOLOR const& color) noexcept : m_width(width), m_color(color) {
		m_vertexList[0] = start;
		m_vertexList[1] = end;
	}

	~DrawLine() = default;

	void			OnRender(float fElapsedTime) {
		g_pLine->SetWidth(m_width);
		g_pLine->Begin();

		g_pLine->DrawTransform(m_vertexList, std::size(m_vertexList), &g_matrix, m_color);

		g_pLine->End();
	}

	void			SetPosition(D3DXVECTOR3 const& start, D3DXVECTOR3 const& end) {
		m_vertexList[0] = start;
		m_vertexList[1] = end;
	}
	void			SetColor(D3DXCOLOR const& color) {
		m_color = color;
	}
	void			SetWidth(float const& width) {
		m_width = width;
	}

private:
	D3DXCOLOR		m_color;
	
	D3DXVECTOR3		m_vertexList[2];
	float			m_width;
};