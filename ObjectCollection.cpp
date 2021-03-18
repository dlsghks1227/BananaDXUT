#include "DXUT.h"
#include "ObjectCollection.h"

ObjectCollection::ObjectCollection() noexcept
{
}

void ObjectCollection::Add(std::shared_ptr<Object> object)
{
	m_newObjects.push_back(object);
}

void ObjectCollection::AllObjectRelelase()
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

void ObjectCollection::ProcessNewObjects()
{
	if (m_newObjects.size() > 0) {
		//for (const auto& item : m_newObjects) {
		//}
		m_objects.assign(m_newObjects.begin(), m_newObjects.end());
		m_newObjects.clear();
	}
}
