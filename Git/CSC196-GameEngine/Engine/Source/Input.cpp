#include "Input.h"
#include <SDL.h>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);

	copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{

}

void Input::Update()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	//keyboard input
	m_prevKeyboardState = m_keyboardState;
	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

	//mouse input
	int x, y;
	uint32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePosition.x = (float)x;
	m_mousePosition.y = (float)y;
	m_prevButtonState = m_buttonState;
	m_buttonState[0] = buttonState & SDL_BUTTON_LMASK;
	//000 <- button state -> 001
	//001 <- button mask  -> 001
	//000 <- false true   -> 001
	m_buttonState[1] = buttonState & SDL_BUTTON_MMASK;
	//000 <- button state -> 010
	//010 <- button mask  -> 010
	//000 <- false true   -> 010
	m_buttonState[2] = buttonState & SDL_BUTTON_RMASK;
	//000 <- button state -> 100
	//100 <- button mask  -> 100
	//000 <- false true   -> 100	

}
