#pragma once
#include "KeyCodes.hpp"

class Input 
{
public:
	Input() = delete;

	static bool IsKeyPressed(KeyCode key);
	static bool IsKeyReleased(KeyCode key);
};