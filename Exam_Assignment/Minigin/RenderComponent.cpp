#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"


RenderComponent::RenderComponent()
{

}

RenderComponent::~RenderComponent()
{
	
}

void RenderComponent::Update(float deltaTime)
{
	m_Width += 5*deltaTime;
}

void RenderComponent::Render()
{
	glm::vec3 position = GetParent()->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*mTexture, position.x,position.y,m_Width,m_Height);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}
