#pragma once
#include <vector>
#include <map>
#include <string>
#include <ctype.h>
#include <cassert>
#include <sstream>
#include "Piece.hpp"
class Board
{
public:
	Board();
	~Board();
	uint8_t m = 0b00110011;
	Piece* get_piece_at_position(const sf::Vector2i& position)const;
	std::map<sf::Vector2i, Piece*> get_all_pieces()const;
	void add_piece(Piece* piece);

	void set_up_board_from_FEN(const std::string& FEN);
private:
	std::map<sf::Vector2i,Piece*> m_pieces;
	static Piece* m_s_null_piece;
};

