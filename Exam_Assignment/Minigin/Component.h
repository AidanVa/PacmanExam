#pragma once
#include "GameObject.h"

class Component
{
public:
	Component();
	virtual ~Component(void);

	void SetParent(dae::GameObject* parent) { m_parentGameObject = parent; };
	dae::GameObject* GetParent() { return m_parentGameObject; };
	virtual void Update(float) { };
	virtual void Render() { };


private:
	dae::GameObject* m_parentGameObject = nullptr;

};

