#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
	
}

TransformComponent::TransformComponent(glm::vec3 transform)
{
	m_Transform = transform;
}

TransformComponent::~TransformComponent()
{
}
