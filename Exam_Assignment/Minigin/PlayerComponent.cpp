#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Enums.h"
#include "RenderComponent.h"


PlayerComponent::PlayerComponent(bool isGhost, int playerNr) :m_IsGhost(isGhost)
{
	float xPos = 0;
	if (playerNr == 2)
		xPos = 580;
	//score board
	auto scoreObject = std::make_shared<dae::GameObject>();
	scoreObject->SetPosition(xPos, 30);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_ScoreText = new TextComponent(std::to_string(m_Score), font);
	scoreObject->AddComponent(m_ScoreText);

	dae::SceneManager::GetInstance().GetScene()->Add(scoreObject);

	//lives
	for (size_t i = 0; i < m_Lives; i++)
	{
		auto lifeObject = std::make_shared<dae::GameObject>();
		lifeObject->SetPosition(xPos + i * 15, 0);
		RenderComponent * renderComp = new RenderComponent();
		renderComp->SetTexture("life.png");
		lifeObject->AddComponent(renderComp);

		dae::SceneManager::GetInstance().GetScene()->Add(lifeObject);
		m_LivesArr.push_back(lifeObject);
	}
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	if (m_RespawnTimer>0)
	{
		m_RespawnTimer -= deltaTime;
		return;
	}

	//save spawn position
	if (m_StartPosition.x < 0)
		m_StartPosition = GetParent()->GetPosition();

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
	TileType tile = scene->CheckPickups(GetParent()->GetPosition());
	if (tile == TileType::PICKUP)
	{
		m_Score++;
		m_ScoreText->SetText(std::to_string(m_Score));
	}
	else if (tile == TileType::DOUBLE_PICKUP)
	{
		m_Score += 10;
		m_ScoreText->SetText(std::to_string(m_Score));
	}

}
void PlayerComponent::SetDirection(Direction direction)
{
	m_TargetDirection = direction;
}

bool PlayerComponent::GhostCollision(glm::vec3 pos)
{
	//respawning
	if (m_RespawnTimer > 0 || m_IsGhost)
		return false;
	

	if (abs(pos.x-GetParent()->GetPosition().x)<13 && abs(pos.y - GetParent()->GetPosition().y)<13)
	{
		if (m_IsPoweredUp)
		{
			m_Score += 25;
			return true;
		}
		else
		{
			Respawn();
		}

	}
	return false;
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

void PlayerComponent::Respawn()
{
	m_Lives--;
	GetParent()->SetPosition(m_StartPosition.x, m_StartPosition.y);

	//delete life sprite
	dae::SceneManager::GetInstance().GetScene()->DeleteObject(m_LivesArr[m_LivesArr.size() - 1]);
	m_LivesArr.erase(m_LivesArr.end()-1);
	m_RespawnTimer = 2;
}

