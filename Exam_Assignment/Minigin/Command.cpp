#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"


Command::Command()
{

}

Command::~Command()
{
}

void Command::Execute(PlayerComponent* player)
{
	UNREFERENCED_PARAMETER(player);

}

void UpCommand::Up(PlayerComponent* player)
{
	player->SetDirection(Direction::UP);
}

void DownCommand::Down(PlayerComponent* player)
{
	player->SetDirection(Direction::DOWN);
}

void RightCommand::Right(PlayerComponent* player)
{
	player->SetDirection(Direction::RIGHT);
}

void LeftCommand::Left(PlayerComponent* player)
{
	player->SetDirection(Direction::LEFT);
}

void StartCommand::Start()
{
	dae::SceneManager::GetInstance().GetScene()->StartLevel();
}

void JoinMsPacmanCommand::JoinMsPacman()
{
	dae::SceneManager::GetInstance().GetScene()->AddPlayer2(false);
}

void JoinGhostCommand::JoinGhost()
{
	dae::SceneManager::GetInstance().GetScene()->AddPlayer2(true);
}

