#include "Move.hpp"
//piece types included in move to allow for a PGN export system
//in the future
Move::Move(const uint8_t& piece_type, const uint8_t& start_index, const uint8_t& end_index)
	:m_piece_type(piece_type),
	 m_start_pos(start_index),
	 m_end_pos(end_index)
{}
