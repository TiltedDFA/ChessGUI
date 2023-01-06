#include "Move.hpp"
Move::Move(const uint8_t*& piece, int index) : piece_type(*piece) {
	++index;
	const int column = index % 8;
	const int row = (index - column) / 8;
	board_coordinates = sf::Vector2i(column, row);
}