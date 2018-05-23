#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"


TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font> font)
	: mNeedsUpdate(true), mText(text), mFont(font), mTexture(nullptr)
{
}


TextComponent::~TextComponent()
{
}

void TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) {
			std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<dae::Texture2D>(texture);
	}
}

void TextComponent::Render()
{
	if (mTexture != nullptr)
	{
		const auto pos = GetParent()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}
