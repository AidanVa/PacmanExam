#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include "Texture2D.h"
#include "SceneObject.h"
#include <string>



class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();
	 
	void Update(float deltaTime);
	void Render();
	void SetTexture(const std::string& filename);
	void SetTexture(const std::string& filename,int frameCount, int frameWidth, int frameHeight);
	void SetSize(float width, float height);

	RenderComponent(const RenderComponent &) = delete;
	RenderComponent(RenderComponent &&) = delete;
	RenderComponent & operator= (const RenderComponent &) = delete;
	RenderComponent & operator= (const RenderComponent &&) = delete;

private:
	std::shared_ptr<dae::Texture2D> mTexture;
	float m_Width = 30;
	float m_Height = 30;

	float m_frameDuration = 0.1f;
	int m_FrameIndex = 0;
	int m_FrameCount = 1;
	float m_FrameTimer = 0;
	int m_FrameWidth = 10;
	int m_FrameHeight = 10;

};
