#pragma once
#include <XInput.h>
#include <memory>
#include "Command.h"


enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY
};

class Input
{
public:
	static Input* GetInputManager();
	void Update();
	bool IsPressed(ControllerButton button) const;
	bool HandleInput();
	void AssignButtons();
private:
	Input();
	static Input* m_inputManager;

	XINPUT_STATE currentState {};
	std::unique_ptr<Command> m_buttonA;
	std::unique_ptr<Command> m_buttonB;
	std::unique_ptr<Command> m_buttonX;
	std::unique_ptr<Command> m_buttonY;
	bool m_buttonADown = false;
	bool m_buttonBDown = false;
	bool m_buttonXDown = false;
	bool m_buttonYDown = false;

	
};

