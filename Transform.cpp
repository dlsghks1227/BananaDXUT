#include "DXUT.h"
#include "Transform.hpp"

Transform::Transform(Object* owner) noexcept
	: Component(owner), m_position(0.0f, 0.0f, 0.0f)
{
}

void Transform::SetPosition(D3DXVECTOR3 pos)
{
	m_position = pos;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR3(x, y, z);
}

void Transform::AddPosition(D3DXVECTOR3 pos)
{
	m_position += pos;
}

void Transform::AddPosition(float x, float y, float z)
{
	m_position += D3DXVECTOR3(x, y, z);
}

const D3DXVECTOR3& Transform::GetPosition() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return m_position;
}
