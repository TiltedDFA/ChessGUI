#pragma once
#include<cctype>
#include <SFML/Graphics.hpp>
struct Move {
public:
	Move();
	Move(const uint8_t*& piece, int old_index,int new_index);
public:
	uint8_t piece_type;
	sf::Vector2i new_board_coordinates;
	sf::Vector2i old_board_coordinates;
};