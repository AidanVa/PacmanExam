#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

namespace dae {
	
	GameObject::~GameObject() = default;

	void GameObject::Update(float deltaTime)
	{
		for (Component* component : m_ComponentArr)
		{
			component->Update(deltaTime);
		}
	}

	void GameObject::Render() const
	{
		for (Component* component : m_ComponentArr)
		{
			component->Render();
		}
	}

	void GameObject::SetTexture(const std::string& filename)
	{
		mTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	}

	void GameObject::SetPosition(float x, float y)
	{
		mTransform.SetPosition(x, y, 0.0f);
	}
}