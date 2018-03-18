#pragma once
#include "GameObject.h"

class Component
{
public:
	Component();
	~Component();

	dae::GameObject* GetParent() { return m_parentGameObject; };
	void Update(float) { };
	void Render() { };


private:
	dae::GameObject* m_parentGameObject = nullptr;

};

