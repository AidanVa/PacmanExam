#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

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
		bool IsPressed(ControllerButton button) const;
		void SetPlayer1(std::shared_ptr<dae::GameObject> player) { m_pPlayer1 = player; }

	private:
		std::shared_ptr<dae::GameObject> m_pPlayer1;
		
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
	};

}
