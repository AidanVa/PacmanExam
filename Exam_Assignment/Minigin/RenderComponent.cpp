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
	m_FrameTimer += deltaTime;
	if (m_FrameTimer>m_frameDuration)
	{
		m_FrameIndex++;
		m_FrameTimer = 0;
		if (m_FrameIndex >= m_FrameCount)
			m_FrameIndex = 0;
	}
}

void RenderComponent::Render()
{
	glm::vec3 position = GetParent()->GetPosition();
	int angle = int(GetParent()->GetAngle());
	//static image render
	if (m_FrameCount <= 1)
		dae::Renderer::GetInstance().RenderTexture(*mTexture, position.x,position.y,m_Width,m_Height);
	//animated image render
	else
		dae::Renderer::GetInstance().RenderTexture(*mTexture, position.x, position.y, angle, m_Width, m_Height,
			float(m_FrameIndex * m_FrameWidth),
			0.0f, m_FrameWidth, m_FrameHeight);

}

void RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
void RenderComponent::SetTexture(const std::string& filename, int frameCount, int frameWidth, int frameHeight)
{
	mTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	m_FrameCount = frameCount;
	m_FrameWidth = frameWidth;
	m_FrameHeight = frameHeight;
}

void RenderComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}
