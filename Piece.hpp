#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include <cctype>
#include <map>
#define SPRITE_MAP_PATH "assets/Chess_Pieces_Sprite.png"
namespace piece_types
{
	 const uint8_t White  = 0b10000000;
	 const uint8_t Black  = 0b01000000;
	 const uint8_t King   = 0b00100000;
	 const uint8_t Queen  = 0b00010000;
	 const uint8_t Bishop = 0b00001000;
	 const uint8_t Knight = 0b00000100;
	 const uint8_t Rook   = 0b00000010;
	 const uint8_t Pawn   = 0b00000001;
}
class Piece
{
public:
	Piece()=delete;
	Piece(const uint8_t& type,const sf::Vector2f& position);

	const sf::Sprite& get_sprite()const;
	void set_sprite_position(const sf::Vector2f& position);
	sf::Vector2f get_sprite_pos()const;
private:
	uint8_t m_piece_type;
	sf::Sprite m_sprite;
};