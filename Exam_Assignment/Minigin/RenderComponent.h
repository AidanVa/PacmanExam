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
	void SetSize(float width, float height);

	RenderComponent(const RenderComponent &) = delete;
	RenderComponent(RenderComponent &&) = delete;
	RenderComponent & operator= (const RenderComponent &) = delete;
	RenderComponent & operator= (const RenderComponent &&) = delete;

private:
	std::shared_ptr<dae::Texture2D> mTexture;
	float m_Width = 30;
	float m_Height = 30;


};
