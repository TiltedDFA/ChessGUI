#pragma once
#include<cctype>
#include <SFML/Graphics.hpp>
struct Move {
public:
	Move() = delete;
	Move(const uint8_t*& piece, int index);
public:
	uint8_t piece_type;
	sf::Vector2i board_coordinates;
};