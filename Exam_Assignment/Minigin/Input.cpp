#include "MiniginPCH.h"
#include "Input.h"

Input *Input::m_inputManager = 0;

Input::Input()
{
	
}

Input* Input::GetInputManager()
{
	if (m_inputManager == nullptr)
	{
		m_inputManager = new Input();
	}
	return m_inputManager;
}


void Input::Update()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);
}

bool Input::IsPressed(ControllerButton button) const
{
	switch(button)
	{
	case ControllerButton::ButtonA: 
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

bool Input::HandleInput()
{
	//a-button
	if (IsPressed(ControllerButton::ButtonA) || GetKeyState('S') & 0x8000)
	{
		if (!m_buttonADown)
		{
			m_buttonA->Execute();
		}
		m_buttonADown = true;
	}
	else
		m_buttonADown = false;
	//b-button
	if (IsPressed(ControllerButton::ButtonB) || GetKeyState('D') & 0x8000)
	{
		if (!m_buttonBDown)
		{
			m_buttonB->Execute();
		}
		m_buttonBDown = true;
	}
	else
		m_buttonBDown = false;
	//a-button
	if (IsPressed(ControllerButton::ButtonX) || GetKeyState('A') & 0x8000)
	{
		if (!m_buttonXDown)
		{
			m_buttonX->Execute();
		}
		m_buttonXDown = true;
	}
	else
		m_buttonXDown = false;
	//y-button
	if (IsPressed(ControllerButton::ButtonY) || GetKeyState('W') & 0x8000)
	{
		if (!m_buttonYDown)
		{
			m_buttonY->Execute();
		}
		m_buttonYDown = true;
	}
	else
		m_buttonYDown = false;

	//exit game or continue
	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		return false;
	}
	return true;
}

void Input::AssignButtons()
{
	m_buttonA = std::make_unique<JumpCommand>();
	m_buttonB = std::make_unique<FireCommand>();
	m_buttonX = std::make_unique<DuckCommand>();
	m_buttonY = std::make_unique<FartCommand>();

}