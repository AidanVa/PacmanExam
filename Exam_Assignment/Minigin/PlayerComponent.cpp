#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"


PlayerComponent::PlayerComponent(bool isGhost, int playerNr) :m_IsGhost(isGhost)
{
	float xPos = 0;
	if (playerNr == 2)
		xPos = 580;
	//score board
	auto scoreObject = std::make_shared<dae::GameObject>();
	scoreObject->SetPosition(xPos, 0);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_ScoreText = new TextComponent(std::to_string(m_Score), font);
	scoreObject->AddComponent(m_ScoreText);
	
	dae::SceneManager::GetInstance().GetScene()->Add(scoreObject);

}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	UpdateMovement(deltaTime);
	//change direction if possible and needed
	std::shared_ptr<dae::Scene> scene = dae::SceneManager::GetInstance().GetScene();
	if (m_Direction != m_TargetDirection)
		if (!scene->CheckCollision(GetParent()->GetPosition(), m_TargetDirection))
		{
			m_Direction = m_TargetDirection;
			GetParent()->SetAngle(float(m_Direction) * 90);
		}

	//check pickups
	if(scene->CheckPickups(GetParent()->GetPosition())==TileType::PICKUP)
	{
		m_Score++;
		m_ScoreText->SetText(std::to_string(m_Score));
	};
}

void PlayerComponent::SetDirection(Direction direction)
{
	m_TargetDirection = direction;
}

void PlayerComponent::UpdateMovement(float deltaTime)
{
	std::shared_ptr<dae::Scene> scene = dae::SceneManager::GetInstance().GetScene();
	glm::vec3 pos = GetParent()->GetPosition();
	float speed = 100;

	//check collision
	if (scene->CheckCollision(GetParent()->GetPosition(), m_Direction))
		speed = 0;
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
	GetParent()->SetPosition(pos.x,pos.y);

	
}

