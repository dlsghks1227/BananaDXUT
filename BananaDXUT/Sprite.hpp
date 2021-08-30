#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "ResourceAllocator.hpp"
#include "Texture.hpp"

#include "Object.hpp"
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

	void		SetEnable(bool const& isEnable)		{ m_isEnable = isEnable; };
	bool const& GetEnable()							{ return m_isEnable; };

private:
	ResourceAllocator<Texture>*		m_allocator;
	std::shared_ptr<Texture>		m_texture;

	bool							m_isEnable;
	int								m_currentTextureID;
};