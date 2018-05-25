#pragma once
#include "Component.h"
#include "Font.h"

class TextComponent :
	public Component
{
public:
	TextComponent(const std::string& text, std::shared_ptr<dae::Font> font);
	~TextComponent();

	void Update(float deltaTime) override;
	void Render();
	void SetText(const std::string& text);


	TextComponent(const TextComponent &) = delete;
	TextComponent(TextComponent &&) = delete;
	TextComponent & operator= (const TextComponent &) = delete;
	TextComponent & operator= (const TextComponent &&) = delete;

protected:
	bool mNeedsUpdate;
	std::string mText;
	std::shared_ptr<dae::Font> mFont;
	std::shared_ptr<dae::Texture2D> mTexture;

};

