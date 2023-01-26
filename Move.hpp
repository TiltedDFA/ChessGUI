#pragma once
#include <cctype>
#include <cstdint>
class Move
{
public:
	Move()=delete;
	Move(uint8_t piece_type, uint8_t start_index, uint8_t end_index);
public:
	uint8_t m_piece_type;
	uint8_t m_start_pos;
	uint8_t m_end_pos;
};

