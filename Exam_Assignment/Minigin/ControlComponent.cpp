#include "MiniginPCH.h"
#include "ControlComponent.h"


ControlComponent::ControlComponent()
{
}


ControlComponent::~ControlComponent()
{
}

void ControlComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	glm::vec3 pos = GetParent()->GetPosition();
	if (GetKeyState('S') & 0x8000)
	{
		GetParent()->SetPosition(pos.x+5,pos.y+5);
	}
}
