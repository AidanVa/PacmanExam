#pragma once
#include "Component.h"
#include "Enums.h"
#include "RenderComponent.h"

class GhostComponent :
	public Component
{
public:
	GhostComponent(RenderComponent* renderComp, std::string texturePath);
	~GhostComponent();

	void Update(float deltaTime);



private:
	void UpdateMovement(float deltaTime);
	void Respawn();

	Direction CalcTargetDir();

	Direction m_Direction = Direction::RIGHT;
	Direction m_TargetDirection = Direction::RIGHT;
	glm::vec3 m_StartPosition = glm::vec3(-50,-50,-50);

	float m_RespawnTimer = 3;

	bool m_Scared = false;
	bool m_TextureScared = false;
	std::string m_TexturePath;
	RenderComponent * m_RenderComp = nullptr;
	
};

