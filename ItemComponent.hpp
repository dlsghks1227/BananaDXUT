#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Object.hpp"
#include "Component.hpp"

class ItemComponent : public Component
{
public:
	ItemComponent(Object* owner) noexcept;
	~ItemComponent();

	void		Initialize(Object* player);

	void		OnUpdate(float fElapsedTime)		override;
	void		OnLateUpdate(float fElapsedTIme)	override;

private:
};

