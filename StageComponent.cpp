#include "DXUT.h"
#include "StageComponent.hpp"

StageComponent::StageComponent(Object* owner) noexcept
	: Component(owner),
	m_player(nullptr),
	m_objectCollection(nullptr),
	m_textureAllocator(nullptr),
	m_mapGridWidth(0),
	m_mapGridHeight(0),
	m_currentLinePosition{-100, -100, 10000, 10000},
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

	auto plane = m_object->m_transform->GetPlane();
	m_mapDirections.insert(std::make_pair(
		MapDirection::Left, D3DXPLANE(plane.a, plane.b, plane.a, plane.d)));

	m_mapDirections.insert(std::make_pair(
		MapDirection::Top, D3DXPLANE(plane.a, plane.b, plane.c, plane.b)));

	m_mapDirections.insert(std::make_pair(
		MapDirection::Right, D3DXPLANE(plane.c, plane.b, plane.c, plane.d)));

	m_mapDirections.insert(std::make_pair(
		MapDirection::Bottom, D3DXPLANE(plane.a, plane.d, plane.c, plane.d)));

	const auto itr = m_mapDirections.find(MapDirection::Right);

	if (itr != m_mapDirections.cend()) {
		m_currentNearLine.first = itr->first;
		m_currentNearLine.second = itr->second;
	}

	for (int x = 0; x < m_mapGridWidth; x++) {
		for (int y = 0; y < m_mapGridHeight; y++) {
			if (x == 0 || y == 0 || x == m_mapGridWidth - 1 || y == m_mapGridHeight - 1) {
				this->ChangeMapInfo(x, y, MapInfo::Paint);
			}
			else
			{
				this->ChangeMapInfo(x, y, MapInfo::None);
			}
		}
	}

	//D3DXVECTOR3 vertex[] = {
	//	{0.0f, 0.0f, 0.0f},
	//	{100.0f, 0.0f, 0.0f},
	//	{0.0f, 50.0f, 0.0f},
	//	{50.0f, 50.0f, 0.0f},
	//	{30.0f, 70.0f, 0.0f},
	//	{50.0f, 70.0f, 0.0f},
	//	{30.0f, 100.0f, 0.0f},
	//	{100.0f, 100.0f, 0.0f},
	//};

	//std::vector<D3DXVECTOR3> vertex;

	//std::sort(vertex.begin(), vertex.end(), [](D3DXVECTOR3 const& a, D3DXVECTOR3 const& b) -> bool {
	//	bool swap = false;
	//	if (a.y < b.y) swap = true;
	//	if (a.y == b.y && a.x < b.x) swap = true;
	//	return swap;
	//	});
}

void StageComponent::OnUpdate(float fElapsedTime)
{
	if (m_player != nullptr) {
		float bestNear = 10000.0f;
		D3DXVECTOR3 bestLine(0.0f, 0.0f, 0.0f);

		for (const auto& itr : m_mapDirections) {
			D3DXVECTOR3 line(0.0f, 0.0f, 0.0f);

			float distance = this->LinePointDistance(&line, itr.second, D3DXVECTOR2(
				m_player->m_transform->GetPosition().x,
				m_player->m_transform->GetPosition().y)
			);

			if (bestNear >= distance) {
				bestNear = distance;
				bestLine = line;
				m_currentNearLine.first = itr.first;
				m_currentNearLine.second = itr.second;
			}
		}

		auto movement = m_player->GetComponent<PlayerComponent>();
		bool isCollided = Collision::BoundingBoxPointCollision(m_object->m_transform->GetPlane(), m_player->m_transform->GetPosition());

		POINT playerPos = this->GetGridPosition(m_player->m_transform->GetPosition());

		if (m_inside != isCollided) {
			m_inside = isCollided;

			if (m_inside == true) {

				std::wcout << playerPos.x << ' ' << playerPos.y << '\n';

				std::wcout << static_cast<int>(movement->GetDirection()) << '\n';
			}

			if (m_inside == false) {

				//this->Fill(resultFillPosX, resultFillPosY, MapInfo::Paint);
				for (auto& itr : m_mapDatas) {
					if (itr.second->m_info == MapInfo::Line) {
						itr.second->m_info = MapInfo::Paint;
					}
				}
			}
		}

		if (m_inside == true && playerPos.x < m_mapGridWidth && playerPos.y < m_mapGridHeight) {
			this->ChangeMapInfo(playerPos.x, playerPos.y, MapInfo::Line);
			D3DXVECTOR2 minPos = this->GetWorldPosition(POINT{ m_currentLinePosition.left, m_currentLinePosition.top });
			D3DXVECTOR2 maxPos = this->GetWorldPosition(POINT{ m_currentLinePosition.right, m_currentLinePosition.bottom });

			m_currentDrawLine.SetPosition(
				D3DXVECTOR3(minPos.x, minPos.y, 0.0f),
				D3DXVECTOR3(maxPos.x, maxPos.y, 0.0f)
			);
			
			if (movement->IsRotated() == true) {
			}
		}
	}
}

void StageComponent::OnLateUpdate(float fElapsedTime)
{
}

void StageComponent::OnRender(float fElapsedTime)
{
	m_currentDrawLine.OnRender(fElapsedTime);

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
		case MapInfo::Paint:
			m_texture->Draw();
			break;
		}
	}
}

float StageComponent::LinePointDistance(D3DXVECTOR3* out, D3DXPLANE const& plane, D3DXVECTOR2 const& point)
{
	float dx = plane.c - plane.a;
	float dy = plane.d - plane.b;

	if ((dx == 0.0f) && (dy == 0.0f)) {
		(*out) = D3DXVECTOR3(plane.a, plane.b, 0.0f);

		dx = point.x - plane.a;
		dy = point.y - plane.b;
		return std::sqrtf((dx * dx) + (dy * dy));
	}

	float t = (((point.x - plane.a) * dx) + ((point.y - plane.b) * dy)) / ((dx * dx) + (dy * dy));

	if (t < 0.0f) {
		(*out) = D3DXVECTOR3(plane.a, plane.b, 0.0f);

		dx = point.x - plane.a;
		dy = point.y - plane.b;
	}
	else if (t > 1.0f) {
		(*out) = D3DXVECTOR3(plane.c, plane.d, 0.0f);

		dx = point.x - plane.c;
		dy = point.y - plane.d;
	}
	else {
		(*out) = D3DXVECTOR3(plane.a + t * dx, plane.b + t * dy, 0.0f);

		dx = point.x - (*out).x;
		dy = point.y - (*out).y;
	}

	return std::sqrtf((dx * dx) + (dy * dy));
}

MapInfo StageComponent::GetMapInfoInPosition(D3DXVECTOR3 const& pos)
{
	POINT point = this->GetGridPosition(pos);
	
	return this->GetMapData(
		point.x,
		point.y
	)->m_info;
}

void StageComponent::Fill(int const& x, int const& y, MapInfo fill)
{
	std::stack<MapData>		toVisit;

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
		}

		if (data.m_posX + 1 < m_mapGridWidth && 
			(this->GetMapData(data.m_posX + 1, data.m_posY)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX + 1, data.m_posY, fill));
		}

		if (data.m_posY - 1 >= 0 && 
			(this->GetMapData(data.m_posX, data.m_posY - 1)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX, data.m_posY - 1, fill));
		}

		if (data.m_posY + 1 < m_mapGridHeight && 
			(this->GetMapData(data.m_posX, data.m_posY + 1)->m_info == MapInfo::None))
		{
			toVisit.push(MapData(data.m_posX, data.m_posY + 1, fill));
		}
	}
}

void StageComponent::ChangeMapInfo(int const& x, int const& y, MapInfo const& info)
{
	m_mapDatas[(x + (m_mapGridWidth * y))] = std::make_shared<MapData>(x, y, info);
}

std::shared_ptr<MapData> const& StageComponent::GetMapData(int const& x, int const& y)
{
	return m_mapDatas[(x + (m_mapGridWidth * y))];
}

D3DXVECTOR2 StageComponent::GetWorldPosition(POINT const& pos, bool center)
{
	return D3DXVECTOR2(
		(static_cast<float>(pos.x * c_gridOffset) - (static_cast<float>(m_object->m_transform->GetRect().right) * 0.5f)),
		(static_cast<float>(pos.y * c_gridOffset) - (static_cast<float>(m_object->m_transform->GetRect().bottom) * 0.5f))
	);
}

POINT StageComponent::GetGridPosition(D3DXVECTOR3 const& pos)
{
	POINT point = POINT{
		static_cast<int>(std::floor(pos.x) - std::floor(m_object->m_transform->GetPosition().x)) / c_gridOffset,
		static_cast<int>(std::floor(pos.y) - std::floor(m_object->m_transform->GetPosition().y)) / c_gridOffset
	};

	if (point.x <= 0)	point.x = 0;
	if (point.y <= 0)	point.y = 0;
	if (point.x >= m_mapGridWidth)	point.x = m_mapGridWidth - 1;
	if (point.y >= m_mapGridHeight)	point.y = m_mapGridHeight - 1;

	return point;
}
