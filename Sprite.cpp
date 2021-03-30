#include "DXUT.h"
#include "Sprite.hpp"

#include "Texture.hpp"

Sprite::Sprite(Object* owner) noexcept 
	: Component(owner), m_currentTextureID(-1), m_isEnable(true)
{
	m_texture = std::make_shared<Texture>();
}

Sprite::~Sprite()
{
	m_texture.reset();
}

void Sprite::LoadTexture(int id)
{
	if (id >= 0 && id != m_currentTextureID) {
		m_currentTextureID = id;
		m_texture = m_allocator->Get(id);

		m_object->m_transform->SetRect(m_texture->GetRect());
		m_object->m_transform->SetScale(m_texture->GetScale());
	}
}

void Sprite::LoadTexture(std::wstring const& path)
{
	if (m_allocator) {
		int textureID = m_allocator->Add(path);
		if (textureID >= 0 && textureID != m_currentTextureID) {
			m_currentTextureID = textureID;
			m_texture = m_allocator->Get(textureID);

			m_object->m_transform->SetRect(m_texture->GetRect());
			m_object->m_transform->SetScale(m_texture->GetScale());
		}
	}
}

void Sprite::SetTextureAllocator(ResourceAllocator<Texture>* allocator)
{
	this->m_allocator = allocator;
}

void Sprite::OnRender(float fElapsedTime)
{
	m_texture->SetRect(m_object->m_transform->GetRect());
	m_texture->SetPosition(m_object->m_transform->GetPosition());
	m_texture->SetOffset(m_object->m_transform->GetOffset());
	m_texture->SetScale(m_object->m_transform->GetScale());
	m_texture->SetAngle(m_object->m_transform->GetAngle());
	if (m_isEnable == true) {
		m_texture->Draw();
	}
}