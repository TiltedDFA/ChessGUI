#pragma once
#include "Board.hpp"
#include "Display.hpp"
class Game
{
public:
	Game();
	void Run();

private:
	Board m_board;
	Display m_display;
	sf::RenderWindow m_window;
};

