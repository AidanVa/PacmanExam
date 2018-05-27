#include "MiniginPCH.h"
#include "GhostComponent.h"
#include "Scene.h"
#include "InputManager.h"


GhostComponent::GhostComponent(RenderComponent * renderComp, std::string texturePath): m_RenderComp(renderComp), m_TexturePath(texturePath)
{
	m_Direction = static_cast<Direction>(rand()%4);
	m_TargetDirection = static_cast<Direction>(rand() % 4);

}


GhostComponent::~GhostComponent()
{
}

void GhostComponent::Update(float deltaTime)
{
	//players
	PlayerComponent* player1 = dae::InputManager::GetInstance().GetPlayer1();
	PlayerComponent* player2 = dae::InputManager::GetInstance().GetPlayer2();
	//check if scared
	if (player1 != nullptr && player1->IsPoweredUp() || player2 != nullptr && player2->IsPoweredUp())
		m_Scared = true;
	else
		m_Scared = false;
	//update texture if needed
	if (m_TextureScared != m_Scared)
	{
		if (m_Scared)
			m_RenderComp->SetTexture("ghostScared.png", 2, 32, 36);
		else
			m_RenderComp->SetTexture(m_TexturePath, 2, 32, 36);

		m_TextureScared = m_Scared;
	}

	if (m_RespawnTimer > 0)
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
	if (m_RespawnTimer<=0)
	{
		if (player1 != nullptr && player1->GhostCollision(GetParent()->GetPosition()))
			Respawn();
		if (player2 != nullptr && player2->GhostCollision(GetParent()->GetPosition()))
			Respawn();
	}
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
		m_TargetDirection = CalcTargetDir();
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

Direction GhostComponent::CalcTargetDir()
{
	PlayerComponent* player1 = dae::InputManager::GetInstance().GetPlayer1();
	PlayerComponent* player2 = dae::InputManager::GetInstance().GetPlayer2();
	//calculate closest target
	glm::vec3 closestTarget = player1->GetParent()->GetPosition();
	glm::vec3 position = GetParent()->GetPosition();

	if (player2 != nullptr)
	{
		float p1Distance = sqrt(pow(closestTarget.x-position.x, 2) + pow(closestTarget.y-position.y, 2));
		glm::vec3 p2Pos = player1->GetParent()->GetPosition();
		float p2Distance = sqrt(pow(p2Pos.x - position.x, 2) + pow(p2Pos.y - position.y, 2));
		if (p2Distance > p1Distance)
			closestTarget = p2Pos;
	}

	//calculate direction
	float horizontalWeight = closestTarget.x - position.x;
	float verticalWeight = closestTarget.y - position.y;
	if (m_Scared)
	{
		horizontalWeight *= -1;
		verticalWeight *= -1;
	}

	if (abs(horizontalWeight) > abs(verticalWeight))
		if (horizontalWeight > 0)
			return Direction::RIGHT;
		else
			return Direction::LEFT;
	else
		if (verticalWeight > 0)
			return Direction::DOWN;
		else
			return Direction::UP;


		


}
