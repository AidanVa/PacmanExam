#pragma once
#include "GameObject.h"
#include "PlayerComponent.h"


class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute(PlayerComponent* player);


};

class UpCommand : public Command
{
public:
	void Execute(PlayerComponent* player) override { Up(player); }

	void Up(PlayerComponent*player);
};

class DownCommand : public Command
{
public:
	void Execute(PlayerComponent* player) override { Down(player); }

	void Down(PlayerComponent* player);
};

class RightCommand : public Command
{
public:
	void Execute(PlayerComponent*player) override { Right(player); }

	void Right(PlayerComponent*player);
};

class LeftCommand : public Command
{
public:
	void Execute(PlayerComponent*player) override { Left(player); }

	void Left(PlayerComponent*player);
};
