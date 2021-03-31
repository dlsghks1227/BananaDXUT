#include "DXUT.h"
#include "StageComponent.hpp"

StageComponent::StageComponent(Object* owner) noexcept
	: Component(owner),
	m_player(nullptr),
	m_objectCollection(nullptr),
	m_textureAllocator(nullptr),
	m_startPosition(0.0f, 0.0f, 0.0f),
	m_mapGridWidth(0),
	m_mapGridHeight(0),
	m_clearMapCount(1.0f),
	m_inside(false)
{
}

StageComponent::~StageComponent()
{
}

void StageComponent::Initialize(
	Object* player, 
	ObjectCollection* objectCollection,
	ResourceAllocator<Texture>* textureAllocator,
	std::wstring const& path)
{
	m_player = player;
	m_objectCollection = objectCollection;
	m_textureAllocator = textureAllocator;

	m_startPosition = m_player->m_transform->GetPosition();

	if (m_textureAllocator) {
		int textureID = m_textureAllocator->Add(path);
		if (textureID >= 0) {
			m_texture = m_textureAllocator->Get(textureID);

			m_object->m_transform->SetRect(m_texture->GetRect());
			m_object->m_transform->SetScale(m_texture->GetScale());
		}
	}

	m_object->m_transform->SetPosition(
		static_cast<float>(m_object->m_transform->GetRect().right) * -0.5f,
		static_cast<float>(m_object->m_transform->GetRect().bottom) * -0.5f,
		1.0f
	);

	m_mapGridWidth = (m_object->m_transform->GetRect().right / c_gridOffset);
	m_mapGridHeight = (m_object->m_transform->GetRect().bottom / c_gridOffset);

	for (int x = 0; x < m_mapGridWidth; x++) {
		for (int y = 0; y < m_mapGridHeight; y++) {
			if (x == 0 || y == 0 || x == m_mapGridWidth - 1 || y == m_mapGridHeight - 1) {
				this->ChangeMapInfo(x, y, MapInfo::Paint);
			}
			else {
				this->ChangeMapInfo(x, y, MapInfo::None);
			}
		}
	}
}

void StageComponent::OnUpdate(float fElapsedTime)
{
	if (m_player != nullptr) {
		auto playerComponent = m_player->GetComponent<PlayerComponent>();
		POINT playerPos = this->GetGridPosition(m_player->m_transform->GetPosition());

		bool isCollided = false;

		if (0 <= playerPos.x && 0 <= playerPos.y && playerPos.x < m_mapGridWidth && playerPos.y < m_mapGridHeight) {
			isCollided = (this->GetMapData(playerPos.x, playerPos.y)->m_info == MapInfo::None || this->GetMapData(playerPos.x, playerPos.y)->m_info == MapInfo::Line);
		}
		else {
			isCollided = false;
		}

		if (m_inside != isCollided) {
			m_inside = isCollided;

			if (m_inside == true) {
				this->UpdateMapLine();
			}

			if (m_inside == false) {
				this->UpdateMapLine();
			}
		}

		if (m_inside == true && playerPos.x < m_mapGridWidth && playerPos.y < m_mapGridHeight) {
			if (this->GetMapData(
				playerPos.x + static_cast<int>(playerComponent->GetVelocity().x), 
				playerPos.y + static_cast<int>(playerComponent->GetVelocity().y))->m_info == MapInfo::Line)
			{
				this->resetPlayer();
			}
			else
			{
				this->ChangeMapInfo(playerPos.x, playerPos.y, MapInfo::Line);
			}
		}
	}
}

void StageComponent::OnRender(float fElapsedTime)
{
	for (auto& itr : m_mapDatas) {
		m_texture->SetRect(
			RECT{ 
				(itr.second->m_posX * c_gridOffset),
				(itr.second->m_posY * c_gridOffset),
				(itr.second->m_posX * c_gridOffset) + c_gridOffset,
				(itr.second->m_posY * c_gridOffset) + c_gridOffset
			}
		);

		D3DXVECTOR2 worldPos = this->GetWorldPosition(POINT{ itr.second->m_posX, itr.second->m_posY });
		m_texture->SetPosition(D3DXVECTOR3(worldPos.x, worldPos.y, 1.0f));

		switch (itr.second->m_info) {
		case MapInfo::Line:
		case MapInfo::Paint:
			m_texture->Draw();
			break;
		}
	}
}

POINT StageComponent::GetGridPosition(D3DXVECTOR3 const& pos)
{
	POINT point = POINT{
		static_cast<int>(std::floor(pos.x) - std::floor(m_object->m_transform->GetPosition().x)) / c_gridOffset,
		static_cast<int>(std::floor(pos.y) - std::floor(m_object->m_transform->GetPosition().y)) / c_gridOffset
	};

	return point;
}

D3DXVECTOR2 StageComponent::GetWorldPosition(POINT const& pos)
{
	return D3DXVECTOR2(
		(static_cast<float>(pos.x * c_gridOffset) - (static_cast<float>(m_object->m_transform->GetRect().right) * 0.5f)),
		(static_cast<float>(pos.y * c_gridOffset) - (static_cast<float>(m_object->m_transform->GetRect().bottom) * 0.5f))
	);
}

MapData* StageComponent::GetMapData(int const& x, int const& y)
{
	if (m_mapDatas.count((x + (m_mapGridWidth * y))) > 0) {
		return m_mapDatas[(x + (m_mapGridWidth * y))].get();
	}
	return nullptr;
}

void StageComponent::resetPlayer()
{
	if (m_player != nullptr) {
		auto playerComponent = m_player->GetComponent<PlayerComponent>();
		playerComponent->Reset(m_startPosition);
		playerComponent->DecreaseHp();

		for (auto& itr : m_mapDatas) {
			if (itr.second->m_info == MapInfo::Line) {
				itr.second->m_info = MapInfo::None;
			}
		}
	}
}

int StageComponent::Fill(int const& x, int const& y, MapInfo fill)
{
	std::stack<MapData>		toVisit;
	int						area = 0;

	toVisit.push(MapData(x, y, fill));

	while (toVisit.empty() == false) {
		MapData data = toVisit.top();
		toVisit.pop();

		if (this->GetMapData(data.m_posX, data.m_posY)->m_info != MapInfo::None) {
			continue;
		}

		this->ChangeMapInfo(data.m_posX, data.m_posY, data.m_info);

		if (data.m_posX - 1 >= 0 && 
			(this->GetMapData(data.m_posX - 1, data.m_posY)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX - 1, data.m_posY, fill));
			area++;
		}

		if (data.m_posX + 1 < m_mapGridWidth && 
			(this->GetMapData(data.m_posX + 1, data.m_posY)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX + 1, data.m_posY, fill));
			area++;
		}

		if (data.m_posY - 1 >= 0 && 
			(this->GetMapData(data.m_posX, data.m_posY - 1)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX, data.m_posY - 1, fill));
			area++;
		}

		if (data.m_posY + 1 < m_mapGridHeight && 
			(this->GetMapData(data.m_posX, data.m_posY + 1)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX, data.m_posY + 1, fill));
			area++;
		}
	}

	return area;
}

void StageComponent::ChangeMapInfo(int const& x, int const& y, MapInfo const& info)
{
	m_mapDatas[(x + (m_mapGridWidth * y))] = std::make_shared<MapData>(x, y, info);
}

void StageComponent::UpdateMapLine()
{
	MapInfo fillData = MapInfo::Compare1;
	MapInfo resultData = MapInfo::Compare1;
	int		bestArea = 0;

	for (int x = 0; x < m_mapGridWidth; x++) {
		for (int y = 0; y < m_mapGridHeight; y++) {
			if (this->GetMapData(x, y)->m_info == MapInfo::None) {
				int area = this->Fill(x, y, fillData);
				if (bestArea <= area) {
					bestArea = area;
					resultData = fillData;
				}
				fillData = MapInfo::Compare2;
			}
		}
	}

	//this->Fill(resultFillPosX, resultFillPosY, MapInfo::Paint);
	for (auto& itr : m_mapDatas) {
		if (itr.second->m_info == resultData) {
			itr.second->m_info = MapInfo::None;
		}
		else if (itr.second->m_info != resultData || itr.second->m_info != MapInfo::None) {
			itr.second->m_info = MapInfo::Paint;
		}
	}

	m_clearMapCount = 0.0f;

	for (auto& itr : m_mapDatas) {
		if (itr.second->m_info == MapInfo::Paint) {
			m_clearMapCount += 1.0f;
		}
	}
}

//float StageComponent::LinePointDistance(D3DXVECTOR3* out, D3DXPLANE const& plane, D3DXVECTOR2 const& point)
//{
//	float dx = plane.c - plane.a;
//	float dy = plane.d - plane.b;
//
//	if ((dx == 0.0f) && (dy == 0.0f)) {
//		(*out) = D3DXVECTOR3(plane.a, plane.b, 0.0f);
//
//		dx = point.x - plane.a;
//		dy = point.y - plane.b;
//		return std::sqrtf((dx * dx) + (dy * dy));
//	}
//
//	float t = (((point.x - plane.a) * dx) + ((point.y - plane.b) * dy)) / ((dx * dx) + (dy * dy));
//
//	if (t < 0.0f) {
//		(*out) = D3DXVECTOR3(plane.a, plane.b, 0.0f);
//
//		dx = point.x - plane.a;
//		dy = point.y - plane.b;
//	}
//	else if (t > 1.0f) {
//		(*out) = D3DXVECTOR3(plane.c, plane.d, 0.0f);
//
//		dx = point.x - plane.c;
//		dy = point.y - plane.d;
//	}
//	else {
//		(*out) = D3DXVECTOR3(plane.a + t * dx, plane.b + t * dy, 0.0f);
//
//		dx = point.x - (*out).x;
//		dy = point.y - (*out).y;
//	}
//
//	return std::sqrtf((dx * dx) + (dy * dy));
//}