#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Component.hpp"

extern D3DXMATRIXA16		g_matrix;
extern LPD3DXLINE			g_pLine;

class DrawRect : public Component
{
public:
	DrawRect(Object* owner) noexcept : Component(owner), m_color(D3DCOLOR_XRGB(0, 255, 255)) {

	}
	~DrawRect() = default;

	void	OnLateUpdate(float fElapsedTime) override {
		auto plane = m_object->m_transform->GetPlane();
		m_vertexList[0] = D3DXVECTOR3(plane.a,	plane.b,	-1.0f);
		m_vertexList[1] = D3DXVECTOR3(plane.c,	plane.b,	-1.0f);
		m_vertexList[2] = D3DXVECTOR3(plane.c,	plane.d,	-1.0f);
		m_vertexList[3] = D3DXVECTOR3(plane.a,	plane.d,	-1.0f);
		m_vertexList[4] = D3DXVECTOR3(plane.a,	plane.b,	-1.0f);
	}

	void	OnRender(float fElapsedTime) override {
		auto plane = m_object->m_transform->GetPlane();
		g_pLine->DrawTransform(m_vertexList, std::size(m_vertexList), &g_matrix, m_color);
	}

	void			SetColor(D3DXCOLOR const& color) {
		m_color = color;
	}

private:
	D3DXCOLOR		m_color;

	D3DXVECTOR3		m_vertexList[5];
};