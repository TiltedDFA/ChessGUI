#include "FEN.hpp"
/*
namespace FEN
{
	//takes in board co ordinates and returns the index of where the equalivent position
	//would be in the board array
	int board_to_index(const sf::Vector2i& pos)
	{
		int val = 0;
		val += pos.x - 1;
		val += 8 * (pos.y - 1);
		return val;
	}
	//takes in board co ordinates of a piece and returns the co ordinates of
	//where the piece sprite should be to represent that piece
	sf::Vector2f board_to_sprite_pos(const sf::Vector2i& pos)
	{
		return sf::Vector2f(static_cast<float>(pos.x - 1) * 100,
			static_cast<float>(pos.y - 1) * 100);
	}
	std::vector<std::string> split(std::string FEN)
	{
		std::vector<std::string> fen_blocks;
		size_t pos = 0;
		while ((pos = FEN.find(' ')) != std::string::npos) {
			fen_blocks.push_back(FEN.substr(0, pos));
			FEN.erase(0, pos + 1);
		}
		assert(fen_blocks.size() == 6);
		return fen_blocks;
	}
	//Will need to return a board and set the "this" of the board class to the returned board instance,
	//Will need to write getters and setters for the board class before implamenting this
	void FEN_to_board(const std::string& FEN)
	{
		std::map<char, uint8_t> piece_translation
		{
			{'K', piece_types::King},
			{'Q', piece_types::Queen},
			{'B', piece_types::Bishop},
			{'N', piece_types::Knight},
			{'R', piece_types::Rook},
			{'P', piece_types::Pawn}
		};
		std::array<Piece*, 64> board{};
		const std::vector<std::string> fen_blocks = split(FEN);
		//handles the piece positions
		int board_y = 8;
		int board_x = 1;
		for(const auto& i : fen_blocks[0])
		{
			if(isdigit(i))
			{
				board_x += i - '0';
			}
			else if(i == '/')
			{
				--board_y;
			}
			else
			{
				uint8_t piece_type = piece_translation[static_cast<char>(toupper(i))]
					| isupper(i) ? piece_types::White : piece_types::Black;
				board[board_to_index(sf::Vector2i(board_x, board_y))]
					= new Piece(piece_type, board_to_sprite_pos(sf::Vector2i(board_x, board_y)));
				++board_x;
			}
		}
		if (fen_blocks[1][0] == 'w')
		{
			
		}
	}

}
*/