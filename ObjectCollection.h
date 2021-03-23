#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Object.hpp"

class ObjectCollection final
{
public:
	ObjectCollection() noexcept;
	~ObjectCollection();

	ObjectCollection(ObjectCollection&&) = default;
	ObjectCollection& operator = (ObjectCollection&&) = default;

	ObjectCollection(ObjectCollection const&) = delete;
	ObjectCollection& operator = (ObjectCollection const&) = delete;


	void	OnUpdate(float fElapsedTime);
	void	OnLateUpdate(float fElapsedTime);

	void	OnRender(float fElapsedTime);

	void	Add(std::shared_ptr<Object> object);

	void	ProcessNewObjects();
	void	ProcessRemovals();

private:
	std::vector<std::shared_ptr<Object>>		m_objects;
	std::vector<std::shared_ptr<Object>>		m_newObjects;
};