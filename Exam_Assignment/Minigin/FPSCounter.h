#pragma once
#include "TextComponent.h"
class FPSCounter :
	public TextComponent
{
public:
	FPSCounter(const std::string& text, std::shared_ptr<dae::Font> font);
	~FPSCounter();

	void Update(float deltaTime) override;

};

