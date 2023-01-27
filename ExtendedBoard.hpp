#pragma once
#include "Board.hpp"
//this class will be for the main board as it will have a lot of
//sprite controlling and manipulation values and the base class
//would not need this. base class will be used to calculate.
class ExtendedBoard :public Board
{
public:
	ExtendedBoard();
	sf::Vector2f index_to_spr_pos(const int& index)const;
	//very specific function designed to convert the pos of the held piece
	//to an index
	int spr_pos_to_index(const sf::Vector2f& pos)const;
	void flip_board();
	void draw_possible_moves(sf::RenderWindow& window)const;
	void draw_board(sf::RenderWindow& window)const;
	void on_click(const sf::Vector2i& mouse_pos);
	void on_release();
private:
	sf::Sprite m_board_spr;
	//stores the index of the held piece, -1 if no piece is held
	int m_held_piece;
	//stores if the board is upright(white at bottom)
	bool m_is_upright;
};

