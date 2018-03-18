#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include "Texture2D.h"
#include "SceneObject.h"
#include <string>



class RenderComponent :
	public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void Render();
	void SetTexture(const std::string& filename);

private:
	std::shared_ptr<dae::Texture2D> mTexture;


};
