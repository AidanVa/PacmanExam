#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>


Command::Command()
{

}

Command::~Command()
{
}

void Command::Execute()
{
}

void JumpCommand::Jump()
{
	std::cout << "You jump: \"boink\"\n";
	//achievement
}

void FireCommand::FireGun()
{
	std::cout << "You shoot: \"pew\"\n";
}

void DuckCommand::Duck()
{
	std::cout << "You duck: \"...\"\n";
}

void FartCommand::Fart()
{
	std::cout << "You fart: \"toot\"\n";
}

