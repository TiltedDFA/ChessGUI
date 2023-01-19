#pragma once
#include "Board.hpp"
class Game
{
public:
	Game();
	void run();
private:
	TextureManager m_instance;
	sf::RenderWindow m_window;
	Board m_main_board;
};

