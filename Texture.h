#pragma once
#include "DXUT.h"
#include "header.hpp"

class Texture
{
public:
	Texture(std::wstring const& path) noexcept;
	~Texture();

	void		Draw(RECT const* rect = nullptr, bool isCenter = true);
	UINT		GetWidth()		{ return m_textureInfo.Width; }
	UINT		GetHeight()		{ return m_textureInfo.Height; }

	void		SetPosition(D3DXVECTOR3 position)	{ m_position = position; };
	D3DXVECTOR3 GetPosition()						{ return m_position; }

	void		SetScale(D3DXVECTOR2 scale)			{ m_scale = scale; }
	D3DXVECTOR2 GetScale()							{ return m_scale; }

	void		SetAngle(float angle)				{ m_angle = angle; }
	float		GetAngle()							{ return m_angle; }

private:
	LPDIRECT3DTEXTURE9		m_texture;
	D3DXIMAGE_INFO			m_textureInfo;

	D3DXVECTOR3				m_position;
	D3DXVECTOR2				m_scale;
	float					m_angle;
};