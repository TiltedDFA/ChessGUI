#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include <cctype>
#ifndef SFML_STATIC
#include <iostream>
#define log(x) std::cout << (x) << "\n"
#else
#define log(x)
#endif
#include <map>
#define SPRITE_MAP_PATH "assets/Chess_Pieces_Sprite.png"
namespace piece_types
{
	 constexpr uint8_t White  = 0b10000000;
	 constexpr uint8_t Black  = 0b01000000;
	 constexpr uint8_t King   = 0b00100000;
	 constexpr uint8_t Queen  = 0b00010000;
	 constexpr uint8_t Bishop = 0b00001000;
	 constexpr uint8_t Knight = 0b00000100;
	 constexpr uint8_t Rook   = 0b00000010;
	 constexpr uint8_t Pawn   = 0b00000001;
}
namespace piece_moves
{
	//stored in terms of indexes of the board
	constexpr int King[] = {-7,-8,-9,-1,1,7,8,9};
	constexpr int Queen[] = 
	{
		-7, -8, -9, -1,1, 7, 8, 9,
		-14,-16,-18,-2,2,14,16,18,
		-21,-24,-27,-3,3,21,24,27,
		-28,-32,-36,-4,4,28,32,36,
		-35,-40,-45,-5,5,35,40,45,
		-42,-48,-54,-6,6,42,48,54,
		-49,-56,-63,-7,7,49,56,63
	};
	constexpr int Bishop[] = {
		-7,	-14,-21,-28,-35,-42,-49,
		-9, -18,-27,-36,-45,-54,-63,
		 7,  14, 21, 28, 35, 42, 49,
		 9,  18, 27, 36, 45, 54, 63
	};
	constexpr int Knight[] = {
		17,15,10,6,-17,-15,-10,-6
	};
	constexpr int Rook[] = {
		-8,-16,-24,-32,-40,-48,-56,
		-1,1,-2,2,-3,3,-4,4,
		-5,5,-6,6,-7,7,8,16,
		24,32,40,48,56
	};
	constexpr int pawn[] = { 8,16 };
}
class Piece
{
public:
	Piece()=delete;
	Piece(const uint8_t& type,const sf::Vector2f& position);

	const sf::Sprite& get_sprite()const;
	void set_sprite_position(const sf::Vector2f& position);
	sf::Vector2f get_sprite_pos()const;
	const uint8_t& get_piece_type()const;

	//checks if this piece is white
	bool is_white()const;
	//checks if the piece inputted is white
	static bool is_white(const uint8_t& piece_type);
private:
	uint8_t m_piece_type;
	sf::Sprite m_sprite;
};