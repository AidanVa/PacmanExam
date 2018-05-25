#include "MiniginPCH.h"
#include "FPSCounter.h"
#include "Renderer.h"


FPSCounter::FPSCounter(const std::string& text, std::shared_ptr<dae::Font> font): TextComponent(text, font)
{
}


FPSCounter::~FPSCounter()
{
}

void FPSCounter::Update(float deltaTime)
{
	//fps count
	mText = std::to_string(int(1/deltaTime));

	//render
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