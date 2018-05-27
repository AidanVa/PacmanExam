#pragma once
#include "Component.h"
#include "Enums.h"
#include "TextComponent.h"

class PlayerComponent :
	public Component
{
public:
	PlayerComponent(bool isGhost, int playerNr);
	~PlayerComponent();

	void Update(float deltaTime);
	void SetDirection(Direction direction);

private:
	void UpdateMovement(float deltaTime);

	Direction m_Direction = Direction::RIGHT;
	Direction m_TargetDirection = Direction::RIGHT;

	//score
	int m_Score = 0;
	TextComponent* m_ScoreText = nullptr;
	bool m_IsGhost = false;


};

