#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "SDL.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "TextObject.h"
#include "Component.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "PlayerComponent.h"
#include "GhostComponent.h"

const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{	
		auto& renderer = dae::Renderer::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();


		auto lastTime = std::chrono::high_resolution_clock::now();
		bool doContinue = true;
		while(doContinue) 
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			//doContinue = input->HandleInput();
			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
    return 0;
}

SDL_Window* window;

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,                    
		480,                    
		SDL_WINDOW_OPENGL       
	);
	if (window == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	dae::Renderer::GetInstance().Init(window);
}

void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	UNREFERENCED_PARAMETER(scene);
	//pacman

	auto startText = std::make_shared<dae::GameObject>();
	startText->SetPosition(230, 230);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	startText->AddComponent(new TextComponent("Press SPACE to start.", font));
	scene.Add(startText);

	auto player2Text = std::make_shared<dae::GameObject>();
	player2Text->SetPosition(25, 450);
	player2Text->AddComponent(new TextComponent("Player 2: Press 'M' or 'G' to join as Ms. Pacman or a ghost.", font));
	
	scene.Add(player2Text);



}

void Cleanup()
{
	dae::Renderer::GetInstance().Destroy();
	dae::InputManager::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

