#include "DXUT.h"
#include "Texture.hpp"

extern LPD3DXSPRITE     g_sprite;
extern D3DXMATRIXA16    g_matrix;

Texture::Texture() noexcept :
	m_texture(nullptr),
	m_textureInfo(),
	m_rect{ 0, 0, 0, 0 },
	m_position(0.0f, 0.0f, 0.0f),
	m_offset(0.0f, 0.0f, 0.0f),
	m_scale(1.0f, 1.0f),
	m_angle(0.0f)
{
}

Texture::~Texture()
{
	SAFE_RELEASE(m_texture);
}

HRESULT Texture::LoadFromFile(std::wstring const& path)
{
	if (m_texture != nullptr) {
		return E_FAIL;
	}

	HRESULT hr = S_OK;
	auto device = DXUTGetD3D9Device();

	V_RETURN(D3DXCreateTextureFromFileEx(
		device,
		path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&m_textureInfo,
		nullptr,
		&m_texture
	));

	m_rect = RECT{
			0,
			0,
			static_cast<LONG>(m_textureInfo.Width),
			static_cast<LONG>(m_textureInfo.Height)
	};

	return S_OK;
}

void Texture::Draw()
{
	if (m_texture != nullptr) {
		D3DXMATRIXA16 matrix;
		D3DXVECTOR2 transform(m_position.x, m_position.y);
		D3DXMatrixIdentity(&matrix);
		D3DXMatrixTransformation2D(&matrix, nullptr, 0.0f, &m_scale, nullptr, D3DXToRadian(m_angle), &transform);

		D3DXVECTOR3 pos(0.0f, 0.0f, m_position.z);
		matrix = matrix * g_matrix;
		g_sprite->SetTransform(&matrix);
		g_sprite->Draw(m_texture, &m_rect, &m_offset, &pos, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void Texture::Release()
{
	SAFE_RELEASE(m_texture);
}