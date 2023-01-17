#include "Board.hpp"
Board::Board()
{
	m_pieces.fill(nullptr);
	m_casteling[0] = { true,true };
	m_casteling[1] = { true,true };
}
void Board::clear_board()
{
	for(auto i = m_pieces.begin(); i != m_pieces.end(); ++i)
	{
		delete *i;
	}
	m_pieces.fill(nullptr);
}
int Board::board_to_index(const sf::Vector2i& pos)
{
	int val = 0;
	val += pos.x - 1;
	val += 8 * (pos.y - 1);
	return val;
}
//takes in board co ordinates of a piece and returns the co ordinates of
//where the piece sprite should be to represent that piece
sf::Vector2f Board::board_to_sprite_pos(const sf::Vector2i& pos)
{
	return sf::Vector2f(static_cast<float>(pos.x - 1) * 100,
		static_cast<float>(pos.y - 1) * 100);
}
std::vector<std::string> Board::split(std::string FEN)
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
void Board::FEN_to_board(const std::string& FEN)
{

#pragma region piece positions
	std::map<char, uint8_t> piece_translation
	{
		{'K', piece_types::King},
		{'Q', piece_types::Queen},
		{'B', piece_types::Bishop},
		{'N', piece_types::Knight},
		{'R', piece_types::Rook},
		{'P', piece_types::Pawn}
	};
	const std::vector<std::string> fen_blocks = split(FEN);
	//handles the piece positions
	int board_y = 8;
	int board_x = 1;
	for (const auto& i : fen_blocks[0])
	{
		if (isdigit(i))
		{
			board_x += i - '0';
		}
		else if (i == '/')
		{
			--board_y;
		}
		else
		{
			uint8_t piece_type = piece_translation[static_cast<char>(toupper(i))]
				| isupper(i) ? piece_types::White : piece_types::Black;
			m_pieces[board_to_index(sf::Vector2i(board_x, board_y))]
				= new Piece(piece_type, board_to_sprite_pos(sf::Vector2i(board_x, board_y)));
			++board_x;
		}
	}
#pragma endregion
#pragma region colour_to_move
	if (fen_blocks[1][0] == 'w')
	{
		m_is_whites_turn = true;
	}
	else
	{
		m_is_whites_turn = false;
	}
#pragma endregion
#pragma region casteling
	m_casteling[0] = { false,false };
	m_casteling[1] = { false,false };
	for (const auto& i : fen_blocks[2])
	{
		switch (i)
		{
		case 'K':
			m_casteling[0][0] = true;
			break;
		case 'k':
			m_casteling[1][0] = true;
			break;
		case 'Q':
			m_casteling[0][1] = true;
			break;
		case 'q':
			m_casteling[1][1] = true;
			break;
		default:
			break;
		}
	}
#pragma endregion
#pragma region en pessant target square
	if (fen_blocks[3][0] == '-')
	{
		//-1 will represent the last move not being a double pawn push
		m_en_pesant_target = -1;
	}
	else
	{
		const short int colour_index = (fen_blocks[3][1] == 2) ? 8 : 48;
		switch (fen_blocks[3][0])
		{
		case 'a':
			m_en_pesant_target = colour_index;
			break;
		case 'b':
			m_en_pesant_target = colour_index + 1;
			break;
		case 'c':
			m_en_pesant_target = colour_index + 2;
			break;
		case 'd':
			m_en_pesant_target = colour_index + 3;
			break;
		case 'e':
			m_en_pesant_target = colour_index + 4;
			break;
		case 'f':
			m_en_pesant_target = colour_index + 5;
			break;
		case 'g':
			m_en_pesant_target = colour_index + 6;
			break;
		case 'h':
			m_en_pesant_target = colour_index + 7;
			break;
		default:
			m_en_pesant_target = -1;
		}
	}
#pragma endregion
	m_num_half_moves = static_cast<short>(std::stoi(fen_blocks[4]));
	m_num_full_moves = static_cast<short>(std::stoi(fen_blocks[5]));
}

ExtendedBoard::ExtendedBoard()
	:Board()
{
	m_board_spr.setTexture(TextureManager::get_texture(BOARD_TEXTURE_PATH));
	m_board_spr.setPosition(sf::Vector2f(0, 0));
}
