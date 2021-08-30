#pragma once
#include "DXUT.h"
#include "header.hpp"

class Texture
{
public:
	Texture() noexcept;
	~Texture();

	HRESULT		LoadFromFile(std::wstring const& path);
	void		Draw();
	void		Release();

	const UINT&			GetWidth()		{ return m_textureInfo.Width; }
	const UINT&			GetHeight()		{ return m_textureInfo.Height; }

	void				SetRect(RECT const& rect)					{ m_rect = rect; }
	const RECT&			GetRect()									{ return m_rect; }

	void				SetPosition(D3DXVECTOR3 const& position)	{ m_position = position; };
	const D3DXVECTOR3&	GetPosition()								{ return m_position; }

	void				SetOffset(D3DXVECTOR3 const& offset)		{ m_offset = offset; }
	const D3DXVECTOR3&	SetOffset() { return m_offset; }

	void				SetScale(D3DXVECTOR2 const& scale)			{ m_scale = scale; }
	const D3DXVECTOR2&	GetScale()									{ return m_scale; }

	void				SetAngle(float const& angle)				{ m_angle = angle; }
	const float&		GetAngle()									{ return m_angle; }


private:
	LPDIRECT3DTEXTURE9		m_texture;
	D3DXIMAGE_INFO			m_textureInfo;

	RECT					m_rect;
	D3DXVECTOR3				m_position;
	D3DXVECTOR3				m_offset;
	D3DXVECTOR2				m_scale;
	float					m_angle;
};