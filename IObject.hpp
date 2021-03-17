#pragma once

// C++/소멸자에 virtual을 쓰는 이유
// http://hyacinth.byus.net/moniwiki/wiki.php/C%2B%2B/%EC%86%8C%EB%A9%B8%EC%9E%90%EC%97%90%20virtual%EC%9D%84%20%EC%93%B0%EB%8A%94%20%EC%9D%B4%EC%9C%A0

class IObject
{
public:
	IObject() noexcept : m_position(0.0f, 0.0f, 0.0f), m_plane(0.0f, 0.0f, 0.0f, 0.0f), m_isEnable(true) {}
	virtual ~IObject() = default;

	virtual void	OnUpdate(float fElapsedTime)		= 0;
	virtual void	OnLateUpdate(float fElapsedTime)	= 0;

	virtual void	OnRender(float fElapsedTime)		= 0;

	D3DXPLANE		GetPlane() {
		return D3DXPLANE(
			m_plane.a + m_position.x,
			m_plane.b + m_position.y,
			m_plane.c + m_position.x,
			m_plane.d + m_position.y
		);
	}
	D3DXVECTOR3		GetPosition() {
		return m_position;
	}
	void			SetEnable(bool enable) {
		m_isEnable = enable;
	}
	bool			GetEnable() {
		return m_isEnable;
	}
protected:
	D3DXVECTOR3		m_position;
	D3DXPLANE		m_plane;

	bool			m_isEnable;
};