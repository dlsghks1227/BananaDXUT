#pragma once

class IObject
{
public:
	virtual void	OnUpdate(float fElapsedTime)		= 0;
	virtual void	OnLateUpdate(float fElapsedTime)	= 0;

	virtual void	OnRender(float fElapsedTime)		= 0;
};