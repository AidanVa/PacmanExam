#pragma once
#include "Component.h"
#include "Enums.h"
class PlayerComponent :
	public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Update(float deltaTime);
	void SetDirection(Direction direction);

private:
	void UpdateMovement(float deltaTime);

	Direction m_Direction = Direction::RIGHT;

};

