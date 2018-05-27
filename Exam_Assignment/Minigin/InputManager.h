#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include "PlayerComponent.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void Destroy();
		bool IsPressed(ControllerButton button) const;
		void SetPlayer1(PlayerComponent* player) { m_pPlayer1 = player; }
		void SetPlayer2(PlayerComponent* player) { m_pPlayer2 = player; }
		PlayerComponent* GetPlayer1() { return m_pPlayer1; };
		PlayerComponent* GetPlayer2() { return m_pPlayer2; };


	private:
		PlayerComponent* m_pPlayer1;
		PlayerComponent* m_pPlayer2;

		
		XINPUT_STATE currentState{};

		std::unique_ptr<Command> m_buttonA;
		std::unique_ptr<Command> m_buttonB;
		std::unique_ptr<Command> m_buttonX;
		std::unique_ptr<Command> m_buttonY;
		bool m_buttonADown = false;
		bool m_buttonBDown = false;
		bool m_buttonXDown = false;
		bool m_buttonYDown = false;

		Command* m_UpCommand = new UpCommand();
		Command* m_DownCommand = new DownCommand();
		Command* m_LeftCommand = new LeftCommand();
		Command* m_RightCommand = new RightCommand();

		Command* m_StartCommand = new StartCommand();
		Command* m_JoinMsPacmanCommand = new JoinMsPacmanCommand();
		Command* m_JoinGhostCommand = new JoinGhostCommand();



	};

}
