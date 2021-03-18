#pragma once
#include "DXUT.h"

class Object;
class Component
{
public:
	Component(Object* owner) noexcept : m_object(owner) {}
	virtual ~Component() = default;

	virtual void	OnCreate() {};

	virtual void	OnUpdate(float fElapsedTime) {};
	virtual void	OnLateUpdate(float fElapsedTime) {};

	virtual void	OnRender(float fElapsedTime) {};

private:
	Object*		m_object;
};