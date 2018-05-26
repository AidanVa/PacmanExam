#include "MiniginPCH.h"
#include "PlayerComponent.h"


PlayerComponent::PlayerComponent()
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Update(float deltaTime)
{
	UpdateMovement(deltaTime);
}

void PlayerComponent::SetDirection(Direction direction)
{
	m_Direction = direction;
	GetParent()->SetAngle(float(direction) * 90);
}

void PlayerComponent::UpdateMovement(float deltaTime)
{
	glm::vec3 pos = GetParent()->GetPosition();
	float speed = 50;

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
}

