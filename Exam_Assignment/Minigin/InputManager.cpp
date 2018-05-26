#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	//commands
	//DOWN
	if (GetKeyState('S') & 0x8000)
	{
		m_DownCommand->Execute(m_pPlayer1);
	}
	if (GetKeyState('W') & 0x8000)
	{
		m_UpCommand->Execute(m_pPlayer1);
	}
	if (GetKeyState('A') & 0x8000)
	{
		m_LeftCommand->Execute(m_pPlayer1);
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_RightCommand->Execute(m_pPlayer1);
	}

	return true;
}

void dae::InputManager::Destroy()
{
	delete m_UpCommand;
	m_UpCommand = nullptr;
	delete m_DownCommand;
	m_DownCommand = nullptr;
	delete m_RightCommand;
	m_RightCommand = nullptr;
	delete m_LeftCommand;
	m_LeftCommand = nullptr;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
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

