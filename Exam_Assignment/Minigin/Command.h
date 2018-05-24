#pragma once


class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute();


};

class JumpCommand : public Command
{
public:
	void Execute() override { Jump(); }

	void Jump();
};

class FireCommand : public Command
{
public:
	void Execute() override { FireGun(); }

	void FireGun();
};

class DuckCommand : public Command
{
public:
	void Execute() override { Duck(); }

	void Duck();
};

class FartCommand : public Command
{
public:
	void Execute() override { Fart(); }

	void Fart();
};
