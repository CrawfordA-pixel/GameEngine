#pragma once
#include "Vector2.h"
#include <vector>
#include <array>

class Input
{
public:
	Input() = default;
	~Input() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	//mouse 
	Vector2 GetMousePosition() { return m_mousePosition;  }
	bool getMouseButtonDown(uint8_t button) { return m_buttonState[button]; }
	bool getPrevMouseButtonDown(uint8_t button) { return m_prevButtonState[button]; }

	//keyboard
	bool getKeyDown(uint8_t key) { return m_keyboardState[key]; }
	bool getPrevKeyDown(uint8_t key) { return m_prevKeyboardState[key]; }

private:

	//mouse inputs
	Vector2 m_mousePosition{0,0};
	std::array<uint8_t,3> m_buttonState{0,0,0};
	std::array<uint8_t,3> m_prevButtonState{0,0,0};

	//keyboard inputs
	std::vector<uint8_t> m_keyboardState;
	std::vector<uint8_t> m_prevKeyboardState;

};