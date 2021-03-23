#include "DXUT.h"
#include "Transform.hpp"

Transform::Transform(Object* owner) noexcept
	: Component(owner), 
	m_rect{ 0, 0, 0, 0 },
	m_position(0.0f, 0.0f, 0.0f),
	m_offset(0.0f, 0.0f, 0.0f),
	m_scale(0.0f, 0.0f),
	m_angle(0.0f)
{
}

void Transform::SetRect(RECT const& rect)
{
	m_rect = rect;
}

void Transform::SetRect(int x, int y, int width, int height)
{
	m_rect = RECT{
		x, y, width, height
	};
}

const RECT& Transform::GetRect() const
{
	return m_rect;
}

void Transform::SetPosition(D3DXVECTOR3 const& pos)
{
	m_position = pos;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR3(x, y, z);
}

void Transform::AddPosition(D3DXVECTOR3 const& pos)
{
	m_position += pos;
}

void Transform::AddPosition(float x, float y, float z)
{
	m_position += D3DXVECTOR3(x, y, z);
}

const D3DXVECTOR3& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetOffset(D3DXVECTOR3 const& offset)
{
	m_offset = offset;
}

void Transform::SetOffset(float x, float y, float z)
{
	m_offset = D3DXVECTOR3(x, y, z);
}

const D3DXVECTOR3& Transform::GetOffset() const
{
	return m_offset;
}

void Transform::SetScale(D3DXVECTOR2 const& scale)
{
	m_scale = scale;
}

void Transform::SetScale(float x, float y)
{
	m_scale = D3DXVECTOR2(x, y);
}

const D3DXVECTOR2& Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetCenter()
{
	m_offset = D3DXVECTOR3(
		static_cast<float>(m_rect.right - m_rect.left) * 0.5f,
		static_cast<float>(m_rect.bottom - m_rect.top) * 0.5f,
		0.0f
	);
}
