#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <SDL_video.h>
#include <SDL.h>
#include "Enums.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "FPSCounter.h"
#include "GhostComponent.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name)
{
	//m_DebugSprite = std::make_shared<dae::GameObject>();
	//m_DebugSprite->SetPosition(80, 50);
	//RenderComponent* renderComponent = new RenderComponent();
	//renderComponent->SetTexture("debug.png");
	//m_DebugSprite->AddComponent(renderComponent);
	//Add(m_DebugSprite);
}

int dae::Scene::GetTileAtPos(glm::vec3 position)
{
	//crash prevention
	if (m_levelMap.size()==0)
	{
		return 0;
	}
	//m_DebugSprite->SetPosition(position.x,position.y);
	position.x = position.x - 640 / 2 + m_GridSize * m_TileSize / 2 - m_TileSize / 2;
	int xIndex = int(position.x / m_TileSize);
	position.y = position.y - 480 / 2 + m_GridSize * m_TileSize / 2 - m_TileSize / 2;
	int yIndex = int(position.y / m_TileSize);

	int index = xIndex+yIndex*m_GridSize;
	//convert back to position
	float posX = float(index % m_GridSize - m_GridSize / 2)*m_TileSize;
	float posY = float(index / m_GridSize - m_GridSize / 2)*m_TileSize;
	//center
	posX += 640 / 2;
	posY += 480 / 2;

	//clamp
	if (index < 0)
		index = 0;
	else if (index >= m_levelMap.size())
		index = int(m_levelMap.size()-1);


	return m_levelMap[index];


}

void dae::Scene::ClearLevel()
{
	mObjects.clear();
	m_pickupsArr.clear();

	dae::InputManager::GetInstance().SetPlayer1(nullptr);
	dae::InputManager::GetInstance().SetPlayer2(nullptr);


}

void dae::Scene::SpawnPlayer(int playerType)
{
	if (playerType == 1)
	{
		//pacman
		auto pacman = std::make_shared<dae::GameObject>();
		pacman->SetPosition(180, 80);
		RenderComponent* renderComponent = new RenderComponent();
		renderComponent->SetTexture("pacman.png", 6, 46, 45);
		pacman->AddComponent(renderComponent);
		PlayerComponent * playerComp = new PlayerComponent(false, 1);
		pacman->AddComponent(playerComp);
		Add(pacman);
		dae::InputManager::GetInstance().SetPlayer1(playerComp);
	}
	else if (playerType == 2)
	{
		//ms pacman
		auto pacman = std::make_shared<dae::GameObject>();
		pacman->SetPosition(460, 80);
		RenderComponent* renderComponent = new RenderComponent();
		renderComponent->SetTexture("msPacman.png", 6, 46, 45);
		pacman->AddComponent(renderComponent);
		PlayerComponent * playerComp = new PlayerComponent(false, 2);
		pacman->AddComponent(playerComp);
		Add(pacman);
		dae::InputManager::GetInstance().SetPlayer2(playerComp);
	}
	else if (playerType == 3)
	{
		//ghost
		auto pacman = std::make_shared<dae::GameObject>();
		pacman->SetPosition(460, 80);
		RenderComponent* renderComponent = new RenderComponent();
		renderComponent->SetTexture("ghostPlayer.png", 2, 32, 36);
		pacman->AddComponent(renderComponent);
		PlayerComponent * playerComp = new PlayerComponent(true, 2);
		pacman->AddComponent(playerComp);
		Add(pacman);
		dae::InputManager::GetInstance().SetPlayer2(playerComp);
	}
}

void dae::Scene::SpawnGhost(int ghostNr, float x, float y)
{
	auto ghost = std::make_shared<dae::GameObject>();
	ghost->SetPosition(x,y);
	RenderComponent* renderComponent = new RenderComponent();
	std::string path;
	switch (ghostNr)
	{
	case 1:
		path = "ghostBlue.png";
		break;
	case 2:
		path = "ghostPink.png";
		break;
	case 3:
		path = "ghostOrange.png";
		break;
	default:
		path = "ghostRed.png";
		break;
	}
	renderComponent->SetTexture(path, 2, 32, 36);
	ghost->AddComponent(renderComponent);
	GhostComponent * ghostComp = new GhostComponent(renderComponent, path);
	ghost->AddComponent(ghostComp);
	Add(ghost);
}

void dae::Scene::SpawnAllGhosts()
{
	SpawnGhost(1, 300, 220);
	SpawnGhost(2, 300, 240);
	SpawnGhost(3, 340, 220);
	SpawnGhost(4, 340, 240);


}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::DeleteObject(const std::shared_ptr<SceneObject>& object)
{
	for (size_t j = 0; j < mObjects.size(); j++)
		if (object.get() == mObjects[j].get())
			mObjects.erase(mObjects.begin() + j);
}

void dae::Scene::Update(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		if (gameObject != 0)
			gameObject->Update(deltaTime);
	}

	//check game completion
	if (m_IsGameRunning && m_pickupsArr.size() == 0)
		EndLevel(true);
	
	if( (InputManager::GetInstance().GetPlayer1()!=nullptr && InputManager::GetInstance().GetPlayer1()->GetLives()<=0 )
		|| (InputManager::GetInstance().GetPlayer2() != nullptr && InputManager::GetInstance().GetPlayer2()->GetLives() <= 0))
		EndLevel(false);



}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

void dae::Scene::LoadLevel(int levelIndex)
{
	//CLEAR EXISTING
	ClearLevel();
	m_IsGameRunning = true;

	//LOAD LEVEL MAP
	switch (levelIndex)
	{
	case 0:
		m_levelMap =
		{ 
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,3,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,3,1,
			1,2,1,1,2,1,2,2,2,1,2,1,2,1,2,1,1,2,1,1,1,2,1,1,1,2,1,
			1,2,1,1,2,1,1,1,1,1,2,1,2,1,2,1,1,2,1,1,1,2,4,2,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,1,3,2,2,1,2,2,1,2,2,2,1,2,1,2,1,
			1,2,1,1,2,1,1,2,1,1,2,1,1,1,2,2,2,2,2,2,2,2,1,2,1,2,1,
			1,2,1,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,2,2,1,2,2,2,1,
			1,2,1,2,1,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,2,1,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,1,2,1,
			1,2,1,2,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,
			1,2,1,2,2,2,4,2,2,2,2,1,1,0,1,1,2,1,2,1,2,1,1,2,1,2,1,
			1,2,2,2,1,2,2,2,2,1,2,1,0,0,0,1,2,2,2,1,2,2,1,2,1,2,1,
			1,2,1,2,2,3,1,1,1,1,2,1,0,0,0,1,2,1,1,1,1,2,1,3,1,2,1,
			1,2,1,2,1,2,1,2,2,2,2,1,1,0,1,1,2,2,2,1,2,2,2,2,2,2,1,
			1,2,1,2,2,2,1,2,1,2,2,2,2,2,2,2,2,1,2,1,2,1,1,1,1,2,1,
			1,2,1,1,1,2,1,2,1,2,2,2,1,1,1,1,2,1,2,2,2,2,2,2,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,1,2,1,1,1,1,1,2,1,1,
			1,2,1,2,2,2,1,2,1,1,1,2,2,2,2,2,2,2,2,2,2,4,2,1,2,1,1,
			1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1,2,1,2,1,2,1,2,1,2,1,1,
			1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,1,2,1,2,1,2,1,2,1,2,2,1,
			1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1,2,1,3,1,2,1,2,1,1,2,1,
			1,2,1,2,2,2,2,2,1,4,1,2,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,
			1,2,1,2,1,1,1,2,1,2,1,2,1,2,1,1,2,1,1,1,2,1,1,1,1,2,1,
			1,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};
		break;
	case 1:
		m_levelMap =
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,3,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,3,1,
			1,2,1,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,2,2,1,2,2,2,1,
			1,2,1,2,1,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,2,1,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,1,3,2,2,1,2,2,1,2,2,2,1,2,1,2,1,
			1,2,1,1,1,2,1,2,1,2,2,2,1,1,1,1,2,1,2,2,2,2,2,2,2,2,1,
			1,2,1,2,1,1,1,2,1,2,1,2,1,2,1,1,2,1,1,1,2,1,1,1,1,2,1,
			1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,1,
			1,2,1,2,1,2,1,2,2,2,2,1,1,2,1,1,2,2,2,1,2,2,2,2,2,2,1,
			1,2,1,2,2,2,1,2,1,2,2,1,1,0,1,1,2,1,2,1,2,1,1,1,1,2,1,
			1,2,1,1,1,2,1,2,1,2,2,1,0,0,0,1,2,1,2,2,2,2,2,2,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,1,2,2,2,1,1,2,1,1,2,1,1,
			1,2,1,1,2,1,2,2,2,1,2,1,1,0,1,1,1,2,1,1,1,2,1,1,1,2,1,
			1,2,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,2,1,1,1,2,4,2,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,4,2,2,1,2,2,1,2,2,2,1,2,2,2,1,
			1,2,1,1,2,1,1,2,1,1,2,1,1,1,2,2,2,2,2,2,2,2,1,2,1,2,1,
			1,2,1,2,1,1,1,2,1,2,1,2,1,2,1,1,2,1,1,1,2,1,1,1,1,2,1,
			1,2,1,2,1,1,1,2,1,2,1,2,1,2,1,1,2,1,1,1,2,1,1,1,1,2,1,
			1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,1,
			1,2,1,2,1,2,1,2,2,2,2,1,1,1,1,1,2,2,2,1,2,2,2,2,2,2,1,
			1,2,1,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,2,2,1,2,2,2,1,
			1,2,1,2,1,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,1,2,1,
			1,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};
		break;
	case 2:
		m_levelMap =
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,4,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,3,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,2,1,
			1,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,3,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,
			1,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,1,
			1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,3,1,1,1,1,2,2,1,
			1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};
		break;
	default:
		break;
	}
	//ADD MAP ELEMENTS

	for (int i = 0; i < m_levelMap.size(); i++)
	{
	
		float posX = float(i % m_GridSize - m_GridSize /2)*m_TileSize;
		float posY = float(i / m_GridSize - m_GridSize /2)*m_TileSize;
		//center
		posX += 640 / 2;
		posY += 480 / 2;

		if (m_levelMap[i]!=0)
		{
			auto object = std::make_shared<dae::GameObject>();
			object->SetPosition(posX, posY);
			RenderComponent * render = new RenderComponent();
			render->SetSize(m_TileSize, m_TileSize);
			switch (m_levelMap[i])
			{
			case 1:
				render->SetTexture("wall.png");
				break;
			case 2:
				render->SetTexture("point.png");
				m_pickupsArr.push_back(object);
				break;
			case 3:
				render->SetTexture("powerup.png",4,32,32);
				m_PowerupsArr.push_back(object);
				break;
			case 4:
				render->SetTexture("cherry.png");
				m_SpecialPickupsArr.push_back(object);
				break;
			default:
				break;
			}
			
			object->AddComponent(render);
			Add(object);
		}
	}
	//LOAD PLAYER
	SpawnPlayer(1);
	//SPAWN GHOSTS
	SpawnAllGhosts();

	//FPS METER
	auto fpsMeter = std::make_shared<dae::GameObject>();
	fpsMeter->SetPosition(0, 400);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	FPSCounter* textComponent = new FPSCounter("Text test", font);
	fpsMeter->AddComponent(textComponent);
	Add(fpsMeter);
}

void dae::Scene::EndLevel(bool win)
{
	m_IsGameRunning = false;
	ClearLevel();
	//end message
	auto scoreObject = std::make_shared<dae::GameObject>();
	scoreObject->SetPosition(120, 0150);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 72);
	if (win)
		scoreObject->AddComponent(new TextComponent("You win.", font));
	else
		scoreObject->AddComponent(new TextComponent("Game Over.", font));

	dae::SceneManager::GetInstance().GetScene()->Add(scoreObject);

	//restart message
	auto startText = std::make_shared<dae::GameObject>();
	startText->SetPosition(230, 230);
	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	startText->AddComponent(new TextComponent("Press SPACE to restart.", font2));
	dae::SceneManager::GetInstance().GetScene()->Add(startText);
}

void dae::Scene::StartLevel()
{
	//check game restart
	if (!m_IsGameRunning)
	{
		m_LevelIndex = (m_LevelIndex + 1) % m_LevelCount;
		LoadLevel((m_LevelIndex));
	}

}

void dae::Scene::AddPlayer2(bool asGhost)
{
	if (InputManager::GetInstance().GetPlayer2() == nullptr)
	{
		if (asGhost)
			SpawnPlayer(3);
		else
			SpawnPlayer(2);
	}
}

glm::vec3 dae::Scene::SnapPosition(glm::vec3 position, Direction direction)
{
	UNREFERENCED_PARAMETER(direction);
	glm::vec3 output = position;
	position.x += m_TileSize / 2 - 1;
	position.y += m_TileSize / 2 - 1;


	position.x = position.x - 640 / 2 + m_GridSize * m_TileSize / 2 - m_TileSize / 2;
	int xIndex = int(position.x / m_TileSize);
	position.y = position.y - 480 / 2 + m_GridSize * m_TileSize / 2 - m_TileSize / 2;
	int yIndex = int(position.y / m_TileSize);

	int index = xIndex + yIndex * m_GridSize;
	//convert back to position
	float posX = float(index % m_GridSize - m_GridSize / 2)*m_TileSize;
	float posY = float(index / m_GridSize - m_GridSize / 2)*m_TileSize;
	//center
	posX += 640 / 2;
	posY += 480 / 2;

	if (direction == Direction::LEFT || direction == Direction::RIGHT)
	{
		output.y = posY;
	}
	if (direction == Direction::UP || direction == Direction::DOWN)
	{
		output.x = posX;
	}

	/*
	if (direction == Direction::LEFT || direction == Direction::RIGHT)
	{
		int modulo = int(output.y) % int(m_TileSize);
		if (modulo>m_TileSize/2)
			output.y += m_TileSize - modulo;
		else
			output.y -= modulo;
	}
	if (direction == Direction::UP || direction == Direction::DOWN)
	{
		int modulo = int(output.x) % int(m_TileSize);
		if (modulo>m_TileSize / 2)
			output.x += m_TileSize - modulo;
		else
			output.x -= modulo;

	}
	*/

	return output;
}

bool dae::Scene::CheckCollision(glm::vec3 position, Direction direction)
{
	glm::vec3 pos1 = position;
	glm::vec3 pos2 = position;

	switch (direction)
	{
	case Direction::UP:
		pos1.x += 2;
		pos1.y -= 2;
		pos2.x += m_TileSize - 2;
		pos2.y -= 2;
		break;
	case Direction::DOWN:
		pos1.x += 2;
		pos1.y += 2 + m_TileSize;
		pos2.x += m_TileSize - 2;
		pos2.y += 2 + m_TileSize;
		break;
	case Direction::LEFT:
		pos1.x -= 2;
		pos1.y += 2;
		pos2.x -= 2;
		pos2.y += m_TileSize - 2;
		break;
	case Direction::RIGHT:
		pos1.x += 2 + m_TileSize;
		pos1.y += 2;
		pos2.x += 2 + m_TileSize;
		pos2.y += m_TileSize - 2;
		break;
	}

	if (GetTileAtPos(pos1) == 1 || GetTileAtPos(pos2) == 1)
		return true;

	return false;
}

TileType dae::Scene::CheckPickups(glm::vec3 position)
{
	//regular pickups
	for (size_t i = 0; i < m_pickupsArr.size(); i++)
		if (abs(position.x - m_pickupsArr[i]->GetPosition().x) < m_TileSize/2 && abs(position.y - m_pickupsArr[i]->GetPosition().y) < m_TileSize/2)
			for (size_t j = 0; j < mObjects.size(); j++)
				if (m_pickupsArr[i].get()==mObjects[j].get())
				{
					m_pickupsArr.erase(m_pickupsArr.begin() + i);
					mObjects.erase(mObjects.begin() + j);
					return TileType::PICKUP;
				}
	//special pickups
	for (size_t i = 0; i < m_SpecialPickupsArr.size(); i++)
		if (abs(position.x - m_SpecialPickupsArr[i]->GetPosition().x) < m_TileSize / 2 && abs(position.y - m_SpecialPickupsArr[i]->GetPosition().y) < m_TileSize / 2)
			for (size_t j = 0; j < mObjects.size(); j++)
				if (m_SpecialPickupsArr[i].get() == mObjects[j].get())
				{
					m_SpecialPickupsArr.erase(m_SpecialPickupsArr.begin() + i);
					mObjects.erase(mObjects.begin() + j);
					return TileType::DOUBLE_PICKUP;
				}
	//powerups
	for (size_t i = 0; i < m_PowerupsArr.size(); i++)
		if (abs(position.x - m_PowerupsArr[i]->GetPosition().x) < m_TileSize / 2 && abs(position.y - m_PowerupsArr[i]->GetPosition().y) < m_TileSize / 2)
			for (size_t j = 0; j < mObjects.size(); j++)
				if (m_PowerupsArr[i].get() == mObjects[j].get())
				{
					m_PowerupsArr.erase(m_PowerupsArr.begin() + i);
					mObjects.erase(mObjects.begin() + j);
					return TileType::POWERUP;
				}

	return TileType::EMPTY;
}




