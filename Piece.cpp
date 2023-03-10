#include "Piece.hpp"
Piece::Piece(const uint8_t& type, const sf::Vector2f& position)
	: m_piece_type(type)
{
	m_sprite.setTexture(TextureManager::get_texture(SPRITE_MAP_PATH));
	int y_pos = 0;
	int x_pos = 0;
	//checks if the piece is white
	if ((m_piece_type & 0b10000000) != 0b10000000)
	{
		y_pos = 100;
	}
	//checks if piece is queen
	if ((m_piece_type & 0b00010000) == 0b00010000)
	{
		x_pos = 100;
	}
	//bishop
	else if ((m_piece_type & 0b00001000) == 0b00001000)
	{
		x_pos = 200;
	}
	//knight
	else if ((m_piece_type & 0b00000100) == 0b00000100)
	{
		x_pos = 300;
	}
	//rook
	else if ((m_piece_type & 0b00000010) == 0b00000010)
	{
		x_pos = 400;
	}
	//pawn
	else if ((m_piece_type & 0b00000001) == 0b00000001)
	{
		x_pos = 500;
	}
	m_sprite.setTextureRect({ x_pos,y_pos,100,100 });
	m_sprite.setPosition(position);
}
void Piece::set_sprite_position(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}
sf::Vector2f Piece::get_sprite_pos() const
{
	return m_sprite.getPosition();
}

const sf::Sprite& Piece::get_sprite() const
{
	return m_sprite;
}
const uint8_t& Piece::get_piece_type() const
{
	return m_piece_type;
}
bool Piece::is_white(const uint8_t& piece_type)
{
	return ((piece_type & piece_types::White) == piece_types::White);
}
bool Piece::is_white() const
{
	return is_white(m_piece_type);
}
