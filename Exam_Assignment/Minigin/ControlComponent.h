#pragma once
#include "Component.h"
class ControlComponent :
	public Component
{
public:
	ControlComponent();
	~ControlComponent();

	void Update(float deltaTime);

};

