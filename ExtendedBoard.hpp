#pragma once
#include "Board.hpp"
//this class will be for the main board as it will have a lot of
//sprite controlling and manipulation values and the base class
//would not need this. base class will be used to calculate.
class ExtendedBoard :public Board
{
public:
	ExtendedBoard();
	void flip_board();
	void draw_board(sf::RenderWindow& window)const;
private:
	sf::Sprite m_board_spr;
	bool m_is_upright;
};

