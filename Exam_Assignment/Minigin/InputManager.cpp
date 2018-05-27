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
	//GENERAL
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_StartCommand->Execute(m_pPlayer1);
	}
	if (GetKeyState('M') & 0x8000)
	{
		m_JoinMsPacmanCommand->Execute(m_pPlayer1);
	}
	//PLAYER1
	if (m_pPlayer1 != nullptr)
	{
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
	}
	//PLAYER2
	if (m_pPlayer2 != nullptr)
	{
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			m_DownCommand->Execute(m_pPlayer2);
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			m_UpCommand->Execute(m_pPlayer2);
		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_LeftCommand->Execute(m_pPlayer2);
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			m_RightCommand->Execute(m_pPlayer2);
		}
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

	delete m_StartCommand;
	m_StartCommand = nullptr;
	delete m_JoinMsPacmanCommand;
	m_JoinMsPacmanCommand = nullptr;
	delete m_JoinGhostCommand;
	m_JoinGhostCommand = nullptr;
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

