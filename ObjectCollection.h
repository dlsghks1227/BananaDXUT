#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "IObject.hpp"

class ObjectCollection final
{
public:
	ObjectCollection() noexcept;
	~ObjectCollection() = default;

	ObjectCollection(ObjectCollection&&) = default;
	ObjectCollection& operator = (ObjectCollection&&) = default;

	ObjectCollection(ObjectCollection const&) = delete;
	ObjectCollection& operator = (ObjectCollection const&) = delete;

	void	Add(std::shared_ptr<IObject> object);
	void	AllObjectRelelase();

	void	OnUpdate(float fElapsedTime);
	void	OnLateUpdate(float fElapsedTime);

	void	OnRender(float fElapsedTime);

	void	ProcessNewObjects();
private:
	std::vector<std::shared_ptr<IObject>>		m_objects;
	std::vector<std::shared_ptr<IObject>>		m_newObjects;
};