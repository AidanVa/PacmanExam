#pragma once
#include "Component.h"
#include <glm/vec3.hpp>

class TransformComponent :
	public Component
{
public:
	TransformComponent();
	TransformComponent(glm::vec3 transform);
	~TransformComponent();


	void SetTransform(glm::vec3 transform) { m_Transform = transform; };
	glm::vec3 GetTransform() { return m_Transform; };


private:
	glm::vec3 m_Transform;
};

