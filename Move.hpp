#pragma once
#include <cctype>
#include <cstdint>
class Move
{
public:
	Move()=delete;
	Move(uint8_t piece_type, uint8_t start_index, uint8_t end_index);
public:
	const uint8_t m_piece_type;
	const uint8_t m_start_pos;
	const uint8_t m_end_pos;
};

