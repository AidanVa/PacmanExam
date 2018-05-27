#include "MiniginPCH.h"
#include "GhostComponent.h"
#include "Scene.h"
#include "InputManager.h"


GhostComponent::GhostComponent()
{
	m_Direction = static_cast<Direction>(rand()%4);
	m_TargetDirection = static_cast<Direction>(rand() % 4);

}


GhostComponent::~GhostComponent()
{
}

void GhostComponent::Update(float deltaTime)
{
	if (m_RespawnTimer>0)
	{
		m_RespawnTimer -= deltaTime;
		return;
	}
	//save spawn position
	if (m_StartPosition.x < 0)
		m_StartPosition = GetParent()->GetPosition();

	//MOVEMENT
	UpdateMovement(deltaTime);
	//change direction if possible and needed
	std::shared_ptr<dae::Scene> scene = dae::SceneManager::GetInstance().GetScene();

	if (m_Direction != m_TargetDirection)
		if (!scene->CheckCollision(GetParent()->GetPosition(), m_TargetDirection))
			m_Direction = m_TargetDirection;


	//check player collision
	PlayerComponent* player1 = dae::InputManager::GetInstance().GetPlayer1();
	PlayerComponent* player2 = dae::InputManager::GetInstance().GetPlayer2();

	if (player1 != nullptr && player1->GhostCollision(GetParent()->GetPosition()))
		Respawn();
	if (player2 != nullptr && player2->GhostCollision(GetParent()->GetPosition()))
		Respawn();

}

void GhostComponent::UpdateMovement(float deltaTime)
{
	std::shared_ptr<dae::Scene> scene = dae::SceneManager::GetInstance().GetScene();
	glm::vec3 pos = GetParent()->GetPosition();
	float speed = 100;

	//check collision
	if (scene->CheckCollision(GetParent()->GetPosition(), m_Direction))
	{
		m_Direction = static_cast<Direction>(rand() % 4);
		m_TargetDirection = static_cast<Direction>(rand() % 4);
	}

	//move
	switch (m_Direction)
	{
	case Direction::RIGHT:
		GetParent()->SetPosition(pos.x + speed * deltaTime, pos.y);
		break;
	case Direction::DOWN:
		GetParent()->SetPosition(pos.x, pos.y + speed * deltaTime);
		break;
	case Direction::LEFT:
		GetParent()->SetPosition(pos.x - speed * deltaTime, pos.y);
		break;
	case Direction::UP:
		GetParent()->SetPosition(pos.x, pos.y - speed * deltaTime);
		break;
	default:break;
	}

	//snap position to grid
	pos = scene->SnapPosition(GetParent()->GetPosition(), m_Direction);
	GetParent()->SetPosition(pos.x, pos.y);


}

void GhostComponent::Respawn()
{
	GetParent()->SetPosition(m_StartPosition.x, m_StartPosition.y);
	m_RespawnTimer = 3;
}
