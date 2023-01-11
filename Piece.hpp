#pragma once
#include <SFML/Graphics.hpp>
#include <cctype>
namespace piece_types
{
	 constexpr uint8_t White = 0b10000000;
	 constexpr uint8_t Black = 0b01000000;
	 constexpr uint8_t King = 0b00100000;
	 constexpr uint8_t Queen = 0b00010000;
	 constexpr uint8_t Bishop = 0b00001000;
	 constexpr uint8_t Knight = 0b00000100;
	 constexpr uint8_t Rook = 0b00000010;
	 constexpr uint8_t Pawn = 0b00000001;
}
class Piece
{
public:
	
};