#include "DXUT.h"
#include "EnemyComponent.hpp"

EnemyComponent::EnemyComponent(Object* owner) noexcept
	: Component(owner),
	m_player(nullptr),
	m_stage(nullptr),
	m_objectCollection(nullptr),
	m_textureAllocator(nullptr),
	m_leftCollisionPosition(0.0f, 0.0f, 0.0f),
	m_rightCollisionPosition(0.0f, 0.0f, 0.0f),
	m_velocity(0.0f, 0.0f, 0.0f),
	m_speed(150.0f),
	m_isLeftCollided(false),
	m_isRightCollided(false)
{
	std::vector<float>	angles;
	for (float i = 1.0f; i < 5.0f; i += 1.0f) {
		angles.push_back(45.0f + (90.0f * i));
	}

	std::random_device rng;
	std::shuffle(angles.begin(), angles.end(), rng);
	m_angle = angles[0];
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::Initialize(
	float speed,
	Object* player, 
	Object* stage, 
	ObjectCollection* objectCollection,
	ResourceAllocator<Texture>* textureAllocator
)
{
	m_speed				= speed;
	m_player			= player;
	m_stage				= stage;
	m_objectCollection	= objectCollection;
	m_textureAllocator	= textureAllocator;

}

void EnemyComponent::OnUpdate(float fElapsedTime)
{
	if (m_player != nullptr && m_stage != nullptr) {
		auto stageComponent = m_stage->GetComponent<StageComponent>();
		m_leftCollisionPosition		= this->GetCollisionPosition(m_angle + 45.0f);
		m_rightCollisionPosition	= this->GetCollisionPosition(m_angle - 45.0f);

		POINT enemyPoint			= stageComponent->GetGridPosition(m_object->m_transform->GetPosition());
		POINT leftCollisionPoint	= stageComponent->GetGridPosition(m_leftCollisionPosition);
		POINT rightCollisionPoint	= stageComponent->GetGridPosition(m_rightCollisionPosition);

		MapData* enemyMapData		= stageComponent->GetMapData(enemyPoint.x, enemyPoint.y);
		MapData* leftMapData		= stageComponent->GetMapData(leftCollisionPoint.x, leftCollisionPoint.y);
		MapData* rightMapData		= stageComponent->GetMapData(rightCollisionPoint.x, rightCollisionPoint.y);

		if (enemyMapData != nullptr && leftMapData != nullptr && rightMapData != nullptr)
		{
			bool isLeftCollded = leftMapData->m_info	== MapInfo::Paint;
			bool isRightCollded = rightMapData->m_info	== MapInfo::Paint;

			if (m_isLeftCollided != isLeftCollded) {
				m_isLeftCollided = isLeftCollded;

				if (m_isLeftCollided == true) {
					m_angle -= 90.0f;
				}
			}

			if (m_isRightCollided != isRightCollded) {
				m_isRightCollided = isRightCollded;

				if (m_isRightCollided == true) {
					m_angle += 90.0f;
				}
			}

			if (enemyMapData->m_info == MapInfo::Paint)
			{
				std::random_device rng;
				std::uniform_int_distribution<int>	widthDist(0, stageComponent->GetMapWidth());
				std::uniform_int_distribution<int>	heightDist(0, stageComponent->GetMapHeight());

				POINT itemPos = {
					widthDist(rng),
					heightDist(rng)
				};

				std::vector<ItemType>	type;
				type.push_back(ItemType::SpeedUp);
				type.push_back(ItemType::HpUp);

				std::shuffle(type.begin(), type.end(), rng);

				CreateItem(stageComponent->GetWorldPosition(itemPos), type[0]);
				m_object->QueueForRemoval();
			}



			if (enemyMapData->m_info == MapInfo::Line || 
				Collision::BoundingBoxPointCollision(
					m_object->m_transform->GetPlane(),
					m_player->m_transform->GetPosition()))
			{
				stageComponent->resetPlayer();
			}
		}
		else if (enemyPoint.x < 0 || enemyPoint.y < 0 || enemyPoint.x > stageComponent->GetMapWidth() || enemyPoint.y > stageComponent->GetMapHeight())
		{
			m_object->QueueForRemoval();
		}
	}
	m_velocity = D3DXVECTOR3(
		std::cos(D3DXToRadian(m_angle)),
		std::sin(D3DXToRadian(m_angle)),
		0.0f);
}

void EnemyComponent::OnLateUpdate(float fElapsedTIme)
{
	m_object->m_transform->AddPosition(m_velocity * m_speed * fElapsedTIme);
}

void EnemyComponent::OnRender(float fElapsedTIme)
{
}

D3DXVECTOR3 EnemyComponent::GetCollisionPosition(float const& angle)
{
	return m_object->m_transform->GetPosition() +
		D3DXVECTOR3(
			(m_object->m_transform->GetScale().x * static_cast<float>(m_object->m_transform->GetRect().right)  * 0.25f) * std::cos(D3DXToRadian(angle)),
			(m_object->m_transform->GetScale().y * static_cast<float>(m_object->m_transform->GetRect().bottom) * 0.25f) * std::sin(D3DXToRadian(angle)),
			-1.0f
		);
}

void EnemyComponent::CreateItem(D3DXVECTOR2 const& pos, ItemType const& type)
{
	std::shared_ptr<Object>		item = std::make_shared<Object>();
	auto itemComponent = item->AddComponent<ItemComponent>();
	itemComponent->Initialize(m_player, type, 4.0f, m_textureAllocator);

	item->m_transform->SetScale(0.2f, 0.2f);
	item->m_transform->SetPosition(D3DXVECTOR3(pos.x, pos.y, -1.0f));
	item->m_transform->SetCenter();

	m_objectCollection->Add(item);
}
