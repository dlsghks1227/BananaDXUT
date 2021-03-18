#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "ResourceAllocator.hpp"
#include "Texture.h"

#include "Component.hpp"

class Sprite : public Component
{
public:
	Sprite(Object* owner) noexcept;
	~Sprite();

	virtual void	OnRender(float fElapsedTime)	override;

	void	LoadTexture(int id);
	void	LoadTexture(std::wstring const& path);
	void	SetTextureAllocator(ResourceAllocator<Texture>* allocator);
private:
	ResourceAllocator<Texture>*		m_allocator;
	std::shared_ptr<Texture>		m_texture;
};