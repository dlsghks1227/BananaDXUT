#pragma once
#include "DXUT.h"
#include "header.hpp"

#include "Collision.hpp"

#include "ResourceAllocator.hpp"
#include "Texture.hpp"

#include "InputManager.hpp"
#include "ObjectCollection.h"

#include "Object.hpp"
#include "Component.hpp"

#include "Sprite.hpp"
#include "Transform.hpp"
#include "PlayerComponent.hpp"

enum class MapDirection : int {
	Left = 0,
	Top,
	Right,
	Bottom
};

enum class MapInfo {
	None = 0,
	Line,
	Paint,
	Compare1,
	Compare2
};

struct MapData {
	MapData(int x, int y, MapInfo info) : m_posX(x), m_posY(y), m_info(info) {}
	int			m_posX;
	int			m_posY;
	MapInfo		m_info;
};


constexpr int	c_gridOffset = 10;
using MapDatas = std::unordered_map<unsigned int, std::shared_ptr<MapData>>;

class StageComponent : public Component
{
public:
	StageComponent(Object* owner) noexcept;
	~StageComponent();

	void		Initialize(
		Object* player, 
		ObjectCollection* objectCollection, 
		ResourceAllocator<Texture>* textureAllocator,
		std::wstring const& path);

	void		OnUpdate(float fElapsedTime) override;

	void		OnRender(float fElapsedTime) override;

	POINT							GetGridPosition(D3DXVECTOR3 const& pos);
	D3DXVECTOR2						GetWorldPosition(POINT const& pos);
	MapData*						GetMapData(int const& x, int const& y);


	int			GetMapWidth()		{ return m_mapGridWidth; }
	int			GetMapHeight()		{ return m_mapGridHeight; }

private:
	int								Fill(int const& x, int const& y, MapInfo fill);
	void							ChangeMapInfo(int const& x, int const& y, MapInfo const& info);

	void							UpdateMapLine();

	Object*							m_player;
	ObjectCollection*				m_objectCollection;
	ResourceAllocator<Texture>*		m_textureAllocator;
	std::shared_ptr<Texture>		m_texture;

	int								m_mapGridWidth;
	int								m_mapGridHeight;

	MapDatas						m_mapDatas;

	bool			m_inside;

	// float		LinePointDistance(D3DXVECTOR3* out, D3DXPLANE const& plane, D3DXVECTOR2 const& point);
};