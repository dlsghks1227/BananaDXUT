#include "DXUT.h"
#include "ObjectCollection.h"

ObjectCollection::ObjectCollection() noexcept
{
}

ObjectCollection::~ObjectCollection()
{
	for (auto& item : m_objects) {
		item.reset();
	}
	for (auto& item : m_newObjects) {
		item.reset();
	}
}

void ObjectCollection::OnUpdate(float fElapsedTime)
{
	for (auto& item : m_objects) {
		if (item->GetEnable() == true) {
			item->OnUpdate(fElapsedTime);
		}
	}
}

void ObjectCollection::OnLateUpdate(float fElapsedTime)
{
	for (auto& item : m_objects) {
		if (item->GetEnable() == true) {
			item->OnLateUpdate(fElapsedTime);
		}
	}
}

void ObjectCollection::OnRender(float fElapsedTime)
{
	for (auto& item : m_objects) {
		if (item->GetEnable() == true) {
			item->OnRender(fElapsedTime);
		}
	}
}

void ObjectCollection::Add(std::shared_ptr<Object> object)
{
	m_newObjects.push_back(object);
}

void ObjectCollection::ProcessNewObjects()
{
	if (m_newObjects.size() > 0) {
		for (const auto& item : m_newObjects) {
			item->OnCreate();
		}
		m_objects.insert(m_objects.end(), m_newObjects.begin(), m_newObjects.end());

		m_newObjects.clear();
	}
}

void ObjectCollection::ProcessRemovals()
{
	auto itr = m_objects.begin();
	while (itr != m_objects.end()) {
		auto obj = **itr;

		if (obj.IsQueuedForRemoval() == true) {
			itr = m_objects.erase(itr);
		}
		else {
			++itr;
		}
	}
}
