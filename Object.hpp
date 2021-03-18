#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Component.hpp"
#include "Transform.hpp"

// C++/소멸자에 virtual을 쓰는 이유
// http://hyacinth.byus.net/moniwiki/wiki.php/C%2B%2B/%EC%86%8C%EB%A9%B8%EC%9E%90%EC%97%90%20virtual%EC%9D%84%20%EC%93%B0%EB%8A%94%20%EC%9D%B4%EC%9C%A0

class Object
{
public:
	Object() noexcept : m_plane(0.0f, 0.0f, 0.0f, 0.0f), m_isEnable(true)
	{
		m_transform = AddComponent<Transform>();
	}
	virtual ~Object() = default;

	void	OnCreate() {
		for (const auto& itr : m_components) {
			itr->OnCreate();
		}
	}

	void	OnUpdate(float fElapsedTime) {
		for (const auto& itr : m_components) {
			itr->OnUpdate(fElapsedTime);
		}
	}

	void	OnLateUpdate(float fElapsedTime) {
		for (const auto& itr : m_components) {
			itr->OnLateUpdate(fElapsedTime);
		}
	}

	void	OnRender(float fElapsedTime) {
		for (const auto& itr : m_components) {
			itr->OnRender(fElapsedTime);
		}
	}

	template<typename T> std::shared_ptr<T>	AddComponent()
	{
		// static_assert
		// https://docs.microsoft.com/ko-kr/cpp/cpp/static-assert?view=msvc-160
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		// dynamic_pointer_cast
		// http://www.cplusplus.com/reference/memory/dynamic_pointer_cast/
		for (const auto& exisitingComponent : m_components) {
			if (std::dynamic_pointer_cast<T>(exisitingComponent)) {
				return std::dynamic_pointer_cast<T>(exisitingComponent);
			}
		}

		std::shared_ptr<T> newComponent = std::make_shared<T>(this);
		m_components.push_back(newComponent);

		return newComponent;
	}

	template<typename T> std::shared_ptr<T>	GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (const auto& exisitingComponent : m_components) {
			if (std::dynamic_pointer_cast<T>(exisitingComponent)) {
				return std::dynamic_pointer_cast<T>(exisitingComponent);
			}
		}

		return nullptr;
	}

	D3DXPLANE		GetPlane() {
		return D3DXPLANE(
			m_plane.a + m_transform->GetPosition().x,
			m_plane.b + m_transform->GetPosition().y,
			m_plane.c + m_transform->GetPosition().x,
			m_plane.d + m_transform->GetPosition().y
		);
	}
	void			SetEnable(bool enable) {
		m_isEnable = enable;
	}
	bool			GetEnable() {
		return m_isEnable;
	}

	std::shared_ptr<Transform>		m_transform;

protected:
	std::vector<std::shared_ptr<Component>>		m_components;
	D3DXPLANE		m_plane;

	bool			m_isEnable;
};