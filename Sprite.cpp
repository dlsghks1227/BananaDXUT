#include "DXUT.h"
#include "Sprite.hpp"

#include "Texture.h"

Sprite::Sprite(Object* owner) noexcept 
	: Component(owner)
{
	m_texture = std::make_shared<Texture>();
}

Sprite::~Sprite()
{
	m_texture.reset();
}

void Sprite::LoadTexture(int id)
{
	if (id >= 0) {
		m_texture = m_allocator->Get(id);
	}
}

void Sprite::LoadTexture(std::wstring const& path)
{
	if (m_allocator) {
		int textureID = m_allocator->Add(path);
		if (textureID >= 0) {
			m_texture = m_allocator->Get(textureID);
		}
	}
}

void Sprite::SetTextureAllocator(ResourceAllocator<Texture>* allocator)
{
	this->m_allocator = allocator;
}

void Sprite::OnRender(float fElapsedTime)
{
	m_texture->Draw();
}
