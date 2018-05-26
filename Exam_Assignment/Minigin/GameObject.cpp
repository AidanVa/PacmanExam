#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "typeinfo"

namespace dae {
	
	GameObject::~GameObject()
	{
		//delte components
		for (Component* pComp : m_ComponentArr)
			if (pComp != 0)
			{
				delete pComp;
				pComp = 0;
			}
	}

	void GameObject::Update(float deltaTime)
	{
		for (Component* component : m_ComponentArr)
		{
			component->Update(deltaTime);
		}
	}

	void GameObject::Render() const
	{
		//Renderer::GetInstance().RenderTexture(*mTexture, mTransform.GetPosition().x, mTransform.GetPosition().y);

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

	void GameObject::AddComponent(Component* newComponent)
	{
		newComponent->SetParent(this);
		m_ComponentArr.push_back(newComponent);
	}
}
