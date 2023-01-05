#pragma once
#include <array>
#include <map>
#include <string>
#include <cassert>
#include <sstream>
#include "Piece.hpp"
class Board
{
public:
	Board();
	~Board();
	//will need to rework how this class is structured to fit the new pieces
	//when init pieces, use binary or
	std::array<uint8_t*, 64> get_piece_array()const;
private:
	void init_board();
private:
	//this will take the 0th index to be A1 and will
	//increase going along. 8th index would be A2
	std::array<uint8_t*, 64> m_board;
	//This is to show who can castle where
	//stored as {white{king,queen},Black{king,queen}}
	std::array<std::array<bool, 2>, 2> m_casteling;
	int m_half_move_num;
	int m_full_move_num;
	bool m_is_whites_turn;
};

