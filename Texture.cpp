#include "DXUT.h"
#include "Texture.h"

extern LPD3DXSPRITE g_sprite;
extern D3DXMATRIXA16 g_matrix;

Texture::Texture(std::wstring const& path) noexcept :
	m_texture(nullptr),
	m_textureInfo(),
    m_position(0.0f, 0.0f, 0.0f),
    m_scale(1.0f, 1.0f),
    m_angle(0.0f)
{
    HRESULT hr = S_OK;

    auto device = DXUTGetD3D9Device();

    if (m_texture == nullptr) {
        V(D3DXCreateTextureFromFileEx(
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
    }
}

Texture::~Texture()
{
    SAFE_RELEASE(m_texture);
}

void Texture::Draw(RECT const* rect, bool isCenter)
{
    if (m_texture != nullptr) {
        D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);
        RECT rc = rect == nullptr ? RECT{ 
            0, 
            0, 
            static_cast<LONG>(m_textureInfo.Width),
            static_cast<LONG>(m_textureInfo.Height)
        } : (*rect);

        if (isCenter == true) {
            center = D3DXVECTOR3(
                (static_cast<float>(rc.right - rc.left) * 0.5f),
                (static_cast<float>(rc.bottom - rc.top) * 0.5f),
                0.0f
            );
        }

        D3DXMATRIXA16 matrix;
        D3DXVECTOR2 transform(m_position.x, m_position.y);
        D3DXMatrixIdentity(&matrix);
        D3DXMatrixTransformation2D(&matrix, nullptr, 0.0f, &m_scale, nullptr, D3DXToRadian(m_angle), &transform);

        matrix = matrix * g_matrix;
        g_sprite->SetTransform(&matrix);
        g_sprite->Draw(m_texture, &rc, &center, nullptr, D3DCOLOR_XRGB(255, 255, 255));
    }
}
