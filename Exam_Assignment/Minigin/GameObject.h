#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

class Component;

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		//legacy function
		void SetTexture(const std::string& filename);

		//transform
		void SetPosition(float x, float y);
		glm::vec3 GetPosition() { return mTransform.GetPosition(); };
		float GetAngle() { return mTransform.GetAngle(); };



		void AddComponent(Component* newComponent);
		std::vector<Component*> GetComponents() { return m_ComponentArr; };
		Component& GetComponentByType(std::string type);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<Component*> m_ComponentArr;
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;
		

	};
}
