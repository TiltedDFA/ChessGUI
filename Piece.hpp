#pragma once
#include <SFML/Graphics.hpp>
enum class PieceType
{
	null = 0,
	k,
	q,
	b,
	n,
	r,
	p,
	K,
	Q,
	B,
	N,
	R,
	P,
};
class Piece
{
public:
	Piece();
	Piece(const PieceType& type, const sf::Vector2i& position);

	PieceType get_piece_type()const;

	sf::Vector2i get_postion()const;
	void set_position(const sf::Vector2i& position);

	char get_piece_char()const;
private:
	PieceType m_piece_type;
	sf::Vector2i m_board_position;
};

class Pawn : public Piece
{
public:
	Pawn();
	Pawn(const PieceType& type, const sf::Vector2i& position);

	bool get_move_state()const;

	void set_move_true();
private:
	bool m_has_moved;
};