#include "Piece.hpp"
Piece::Piece()
	:m_piece_type(PieceType::null),m_board_position({0,0})
{}

Piece::Piece(const PieceType& type, const sf::Vector2i& position)
	:m_piece_type(type),m_board_position(position)
{}

PieceType Piece::get_piece_type() const
{
	return m_piece_type;
}

sf::Vector2i Piece::get_postion()const
{
	return m_board_position;
}

void Piece::set_position(const sf::Vector2i& position)
{
	m_board_position = position;
}
char Piece::get_piece_char()const
{
	switch (m_piece_type)
	{
	case PieceType::null:
		return '\0';
	case PieceType::K:
		return 'K';
	case PieceType::Q:
		return 'Q';
	case PieceType::B:
		return 'B';
	case PieceType::N:
		return 'N';
	case PieceType::R:
		return 'R';
	case PieceType::P:
		return 'P';
	case PieceType::k:
		return 'k';
	case PieceType::q:
		return 'q';
	case PieceType::b:
		return 'b';
	case PieceType::n:
		return 'n';
	case PieceType::r:
		return 'r';
	case PieceType::p:
		return 'p';
	}
	return '\0';
}

Pawn::Pawn()
	: Piece(),m_has_moved(false)
{}

Pawn::Pawn(const PieceType& type, const sf::Vector2i& position)
	:Piece(type,position),m_has_moved(false)
{}

bool Pawn::get_move_state() const
{
	return m_has_moved;
}

void Pawn::set_move_true()
{
	m_has_moved = true;
}
