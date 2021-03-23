#pragma once
#include "DXUT.h"
#include "header.hpp"
#include "Texture.hpp"

template<typename T>
class ResourceAllocator
{
public:
	int		Add(std::wstring const& path) {
		auto itr = m_resources.find(path);
		if (itr != m_resources.end()) {
			return itr->second.first;
		}

		std::shared_ptr<T>	resource = std::make_shared<T>();
		if (FAILED(resource->LoadFromFile(path))) {
			return -1;
		}

		m_resources.insert(std::make_pair(path, std::make_pair(m_currentId, resource)));

		return m_currentId++;
	}

	void	Remove(int id) {
		for (const auto& itr : m_resources) {
			if (itr.second.first == id) {
				m_resources.erase(itr.first);
			}
		}
	}

	void	AllRemove() {
		for (const auto& itr : m_resources) {
			itr.second.second->Release();
		}
	}

	std::shared_ptr<T>		Get(int id) {
		for (const auto& itr : m_resources) {
			if (itr.second.first == id) {
				return itr.second.second;
			}
		}

		return nullptr;
	}

	bool	Has(int id) {
		return (this->Get(id) != nullptr);
	}

private:
	int				m_currentId = 0;
	std::map<std::wstring, std::pair<int, std::shared_ptr<T>>> m_resources;
};