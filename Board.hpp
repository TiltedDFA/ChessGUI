#pragma once
#define BOARD_TEXTURE_PATH "assets/board.png"
#include "Piece.hpp"
#include "Move.hpp"
#include <array>
#include <vector>
//This class will be used to represent possible positions
//in future calculations
class Board
{
public:
	Board();
	void clear_board();
	void init_start_board();
protected:
	std::array<Piece*, 64> m_pieces;
	//will store all the past moves in board
	std::vector<Move> m_past_moves;
	//[white = 0, black = 1]
	//[king side = 0, queen side = 1]
	std::array<std::array<bool,2>,2> m_casteling;
	//to keep track of who's move is next
	bool m_is_whites_turn;
	//tracks the number of half moves used to enforce the 50 move rule
	short int m_num_half_moves;
	//tracks the number of full moves
	short int m_num_full_moves;
};
//This class should be the only board 
class ExtendedBoard  : public Board
{
public:
	ExtendedBoard();
private:
	std::vector<Move> m_possible_moves;
	sf::Sprite m_board_spr;
};
