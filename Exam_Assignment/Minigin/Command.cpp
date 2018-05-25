#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>


Command::Command()
{

}

Command::~Command()
{
}

void Command::Execute(std::shared_ptr<dae::GameObject> player)
{
	UNREFERENCED_PARAMETER(player);

}

void UpCommand::Up(std::shared_ptr<dae::GameObject> player)
{
	glm::vec3 pos = player->GetPosition();

	player->SetPosition(pos.x, pos.y - 5);
}

void DownCommand::Down(std::shared_ptr<dae::GameObject> player)
{
	glm::vec3 pos = player->GetPosition();
	
	player->SetPosition(pos.x, pos.y + 5);
}

void RightCommand::Right(std::shared_ptr<dae::GameObject> player)
{
	glm::vec3 pos = player->GetPosition();

	player->SetPosition(pos.x + 5, pos.y);
}

void LeftCommand::Left(std::shared_ptr<dae::GameObject> player)
{
	glm::vec3 pos = player->GetPosition();

	player->SetPosition(pos.x - 5, pos.y);
}

