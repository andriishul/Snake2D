// Snake2D.cpp : Defines the entry point for the application.
//
#include "Snake2D.h"

int main() 
{
	try
	{
		SnakeGame game;
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return getchar();
}
