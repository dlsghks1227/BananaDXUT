#pragma once
#include "DXUT.h"
#include "header.hpp"
#include "Component.hpp"

class Transform : public Component
{
public:
	Transform(Object* owner) noexcept;
	~Transform() = default;

	void				SetRect(RECT const& rect);
	void				SetRect(int x, int y, int width, int height);

	const RECT&			GetRect() const;

	void				SetPosition(D3DXVECTOR3 const& pos);
	void				SetPosition(float x, float y, float z);

	void				AddPosition(D3DXVECTOR3 const& pos);
	void				AddPosition(float x, float y, float z);

	const D3DXVECTOR3&	GetPosition() const;

	void				SetOffset(D3DXVECTOR3 const& offset);
	void				SetOffset(float x, float y, float z);

	const D3DXVECTOR3&	GetOffset() const;

	void				SetScale(D3DXVECTOR2 const& scale);
	void				SetScale(float x, float y);

	const D3DXVECTOR2&	GetScale() const;

	void				SetCenter();

	const D3DXPLANE		GetPlane() {
		return D3DXPLANE(
			((static_cast<float>(m_rect.left)	- m_offset.x) * m_scale.x) + m_position.x,
			((static_cast<float>(m_rect.top)	- m_offset.y) * m_scale.y) + m_position.y,
			((static_cast<float>(m_rect.right)	- m_offset.x) * m_scale.x) + m_position.x,
			((static_cast<float>(m_rect.bottom) - m_offset.y) * m_scale.y) + m_position.y
		);
	}
private:
	RECT				m_rect;
	D3DXVECTOR3			m_position;
	D3DXVECTOR3			m_offset;
	D3DXVECTOR2			m_scale;
	float				m_angle;
};

