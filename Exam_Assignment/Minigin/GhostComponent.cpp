#include "MiniginPCH.h"
#include "GhostComponent.h"


GhostComponent::GhostComponent()
{
	m_StartPosition = GetParent()->GetPosition();
}


GhostComponent::~GhostComponent()
{
}

void GhostComponent::Update(float deltaTime)
{
	//save spawn position
	if (m_StartPosition.x < 0)
		m_StartPosition = GetParent()->GetPosition();

	UpdateMovement(deltaTime);
}

void GhostComponent::UpdateMovement(float deltaTime)
{
}
