#pragma once
#include "Component.hpp"

class Transform : public Component
{
public:
	Transform(Object* owner) noexcept;
	~Transform() = default;

	void				SetPosition(D3DXVECTOR3 pos);
	void				SetPosition(float x, float y, float z);

	void				AddPosition(D3DXVECTOR3 pos);
	void				AddPosition(float x, float y, float z);

	const D3DXVECTOR3&	GetPosition() const;
private:
	D3DXVECTOR3			m_position;
};

