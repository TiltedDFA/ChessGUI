#pragma once
#define BOARD_WHITE_TEXTURE_PATH "assets/board_white.png"
#define BOARD_BLACK_TEXTURE_PATH "assets/board_black.png"
#define STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TEST_FEN1 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define TEST_FEN2 "5r2/8/1R6/ppk3p1/2N3P1/P4b2/1K6/5B2 w - - 0 1"
#define TEST_FEN3 "3qk2r/prp3pp/5n2/3Nn3/1b4P1/4P3/PP3P1P/R1B2RK1 w k - 1 14"
#include "Piece.hpp"
#include "Move.hpp"
#include <array>
#include <vector>
//This class will be used to represent possible positions
//in future calculations
class Board
{
public:
	//static functions
	static sf::Vector2f board_to_sprite_pos(const sf::Vector2i& pos);
	static int board_to_index(const sf::Vector2i& pos);
	static std::vector<std::string> split(std::string FEN);
	static bool out_of_bounds(const int& index);
	
	//board control functions
	Board();
	void clear_board();
	void init_start_board();
	void FEN_to_board(const std::string& FEN);
	//piece functions

	//move functions
	//target_index = index you are trying to move to
	//piece_is_white = the colour of the piece you are trying to move
	bool is_valid_move(const int& target_index, const bool& piece_is_white)const;
	std::vector<Move> generate_possible_moves_for_piece(const int& index)const;
	//this function will not do error checking so it assumes you've already done that
	void make_move(const Move& move);
	static constexpr std::array<std::array<int, 8>, 64> PreComputeData() {
		std::array<std::array<int, 8>, 64> temp_array{};
		for (int file = 0; file < 8; ++file)
		{
			for (int rank = 0; rank < 8; ++rank)
			{
				const int num_north = 7 - rank;
				const int num_east = 7 - file;
				const int num_south = rank;
				const int num_west = file;

				const int index = rank * 8 + file;
				temp_array[index] = {
					num_north,
					num_east,
					num_south,
					num_west,
					std::min(num_north,num_east),
					std::min(num_east,num_south),
					std::min(num_south,num_west),
					std::min(num_north,num_west)
				};
			}
		}

		return temp_array;
	}
private:
	static inline const std::array<std::array<int, 8>, 64> distance_to_edge = PreComputeData();
protected:
	std::array<Piece*, 64> m_pieces;
	//will store all the past moves in board
	std::vector<Move> m_past_moves;
	//[white = 0, black = 1]
	//[king side = 0, queen side = 1]
	std::array<std::array<bool,2>,2> m_casteling;
	//to keep track of who's move is next
	bool m_is_whites_turn;
	//tracks the number of half moves used to enforce the 50 move rule
	short int m_num_half_moves;
	//tracks the number of full moves
	short int m_num_full_moves;
	//tracks the last double pawn push
	//this will store the location as the array index
	short int m_en_pesant_target;
	//holds the board sprite
};
