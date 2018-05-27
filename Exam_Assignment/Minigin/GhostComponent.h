#pragma once
#include "Component.h"
#include "Enums.h"

class GhostComponent :
	public Component
{
public:
	GhostComponent();
	~GhostComponent();

	void Update(float deltaTime);


private:
	void UpdateMovement(float deltaTime);
	void Respawn();

	Direction m_Direction = Direction::RIGHT;
	Direction m_TargetDirection = Direction::RIGHT;
	glm::vec3 m_StartPosition = glm::vec3(-50,-50,-50);

	float m_RespawnTimer = 3;

	bool m_Scared = false;
};

