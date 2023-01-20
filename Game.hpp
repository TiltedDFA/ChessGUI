#pragma once
#include "ExtendedBoard.hpp"
class Game
{
public:
	Game();
	void run();
	//FEN fully works now, might want to add a board co-ordinate system
private:
	TextureManager m_instance;
	sf::RenderWindow m_window;
	ExtendedBoard m_main_board;
};

