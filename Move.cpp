#include "Move.hpp"

//default ctor used to give the attributes values which will
//represent them being uninitalized with game values
Move::Move() :
piece_type(0b11111111),
new_board_coordinates(sf::Vector2i(-1,-1)),
old_board_coordinates(sf::Vector2i(-1,-1))
{}

Move::Move(const uint8_t*& piece, int old_index, int new_index) : piece_type(*piece) {
	++old_index;
	int column = old_index % 8;
	int row = (old_index - column) / 8;
	old_board_coordinates = sf::Vector2i(column, row);
	++new_index;
	column = new_index % 8;
	row = (new_index - column) / 8;
	new_board_coordinates = sf::Vector2i(column, row);
}