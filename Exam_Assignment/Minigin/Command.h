#pragma once
#include "GameObject.h"


class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute(std::shared_ptr<dae::GameObject> player);


};

class UpCommand : public Command
{
public:
	void Execute(std::shared_ptr<dae::GameObject> player) override { Up(player); }

	void Up(std::shared_ptr<dae::GameObject>player);
};

class DownCommand : public Command
{
public:
	void Execute(std::shared_ptr<dae::GameObject> player) override { Down(player); }

	void Down(std::shared_ptr<dae::GameObject> player);
};

class RightCommand : public Command
{
public:
	void Execute(std::shared_ptr<dae::GameObject>player) override { Right(player); }

	void Right(std::shared_ptr<dae::GameObject>player);
};

class LeftCommand : public Command
{
public:
	void Execute(std::shared_ptr<dae::GameObject>player) override { Left(player); }

	void Left(std::shared_ptr<dae::GameObject>player);
};
