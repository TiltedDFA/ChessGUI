#include "Board.hpp"
#include <vector>
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
void Board::init_start_board()
{
	FEN_to_board(TEST_FEN3);
}
int Board::board_to_index(const sf::Vector2i& pos)
{
	int val = 0;
	val += pos.x - 1;
	val += 8 * (pos.y - 1);
	return val;
}
bool Board::out_of_bounds(const int& index)
{
	return (index > 63 || index < 0);
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
	//for some reason this function only works if fen_blocks is static
	std::vector<std::string> fen_blocks = std::vector<std::string>();
	size_t pos = 0;
	while ((pos = FEN.find(' ')) != std::string::npos) {
		std::string substring = FEN.substr(0, pos);
		fen_blocks.push_back(substring);
		FEN.erase(0, pos + 1);
	}
	fen_blocks.push_back(FEN);
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
	int board_x = 8;
	for (const auto& i : fen_blocks[0])
	{
		if (isdigit(i))
		{
			board_x -= i - '0';
		}
		else if (i == '/')
		{
			--board_y;
			board_x = 8;
		}
		else
		{
			uint8_t piece_type = piece_translation[static_cast<char>(toupper(i))]
			| (isupper(i) ? piece_types::White : piece_types::Black);

			m_pieces[board_to_index(sf::Vector2i(board_x, board_y))]
				= new Piece(piece_type, board_to_sprite_pos(sf::Vector2i(abs(board_x-9), abs(board_y-9))));
			--board_x;
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
bool Board::is_valid_move(const int& target_index, const bool& piece_is_white)const
{
	if (out_of_bounds(target_index))
		return false;

	return (m_pieces[target_index] == nullptr ||
		m_pieces[target_index]->is_white() != piece_is_white);
}
//this is pseudo legal rn
std::vector<Move> Board::generate_possible_moves_for_piece(const uint8_t& index)const
{//need to add enspeasnt
	const bool is_white = Piece::is_white(static_cast<int>(m_pieces[index]->get_piece_type()));
	const uint8_t piece_type = static_cast<int>(m_pieces[index]->get_piece_type());
	std::vector<Move> return_value{};
	if((piece_type & piece_types::King) == piece_types::King)
	{
		//all non-casteling moves
		for(const auto& i : piece_moves::King)
		{
			if(is_valid_move(index+i,is_white))
			{
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
					index, static_cast<uint8_t>(index + i));
			}
		}
		if(is_white)
		{
			//king side castling
			if(m_casteling[0][0])
			{
				if(m_pieces[5] == nullptr && m_pieces[6] == nullptr)
				{
					return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
						index, static_cast<uint8_t>(index + 2));
				}
			}
			//queen side
			if(m_casteling[0][1])
			{
				if(m_pieces[1] == nullptr && m_pieces[2] == nullptr && m_pieces[3] == nullptr)
				{
					return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
						index, static_cast<uint8_t>(index - 2));
				}
			}
		}
		else
		{
			//king side
			if (m_casteling[1][0])
			{
				if (m_pieces[61] == nullptr && m_pieces[62] == nullptr)
				{
					return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
						index, static_cast<uint8_t>(index + 2));
				}
			}
			//queen side
			if (m_casteling[1][1])
			{
				if (m_pieces[57] == nullptr && m_pieces[58] == nullptr && m_pieces[59] == nullptr)
				{
					return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
						index, static_cast<uint8_t>(index - 2));
				}
			}
		}
	}
	else if ((piece_type & piece_types::Queen) == piece_types::Queen)
	{
		/*for (int i = 0; i < 56;)
		{
			if (is_valid_move(index + piece_moves::Queen[i], is_white))
			{
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
					index, static_cast<uint8_t>(index + piece_moves::Queen[i]));
			}
			else
			{
				i += (7 - (i % 7));
				continue;
			}
			++i;
		}
		*/
		for(int direction_index = 0; direction_index < 8; ++direction_index)
		{
			for(int i = 0; i < Board::distance_to_edge[index][direction_index];++i)
			{
				const int target_sqr = index + piece_moves::Queen[direction_index] * (i + 1);
				if(m_pieces[index]->is_white() && is_white)
					break;
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
					index, static_cast<uint8_t>(target_sqr));
				if(m_pieces[index]->is_white() && !is_white)
					break;
			}
		}
	}
	else if ((piece_type & piece_types::Bishop) == piece_types::Bishop)
	{
		for (int i = 0; i < 28;)
		{
			if (is_valid_move(index + piece_moves::Bishop[i], is_white))
			{
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
					index, static_cast<uint8_t>(index + piece_moves::Bishop[i]));
			}
			else
			{
				i += (7 - (i % 7));
				continue;
			}
			++i;
		}
	}
	else if ((piece_type & piece_types::Knight) == piece_types::Knight)
	{
		for (const auto& i : piece_moves::Knight)
		{
			if (is_valid_move(index + i, is_white))
			{
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()), index, static_cast<uint8_t>(index + i));
			}
		}
	}
	else if ((piece_type & piece_types::Rook) == piece_types::Rook)
	{
		//NEED TO ACCOUNT FOR CASTELING
		for (int i = 0; i < 28;)
		{
			if (is_valid_move(index + piece_moves::Rook[i], is_white))
			{
				return_value.emplace_back(static_cast<int>(m_pieces[index]->get_piece_type()),
					index, static_cast<uint8_t>(index + piece_moves::Rook[i]));
			}
			else
			{
				i += (7 - (i % 7));
				continue;
			}
			++i;
		}
	}
	else if ((piece_type & piece_types::Pawn) == piece_types::Pawn)
	{
		if(is_white)
		{
			//checks if the pawn is on the second row
			if(static_cast<int>(std::floor(index/8)) == 1)
			{
				if(m_pieces[index+8] == nullptr && m_pieces[index+16] == nullptr)
				{
					return_value.emplace_back(m_pieces[index]->get_piece_type(),
						index, static_cast<uint8_t>(index + 16));
				}
			}
			if(!out_of_bounds(index+8))
			{
				if(m_pieces[index+8] == nullptr)
				{
					return_value.emplace_back(m_pieces[index]->get_piece_type(),
						index, static_cast<uint8_t>(index + 8));
				}
				if(m_pieces[index+7]!= nullptr)
				{
					if(!m_pieces[index+7]->is_white())
					{
						return_value.emplace_back(m_pieces[index]->get_piece_type(),
							index, static_cast<uint8_t>(index + 7));
					}
				}
			}
			if(!out_of_bounds(index+9))
			{
				if (m_pieces[index + 9] != nullptr)
				{
					if (!m_pieces[index + 9]->is_white())
					{
						return_value.emplace_back(m_pieces[index]->get_piece_type(),
							index, static_cast<uint8_t>(index + 9));
					}
				}
			}
		}
		else
		{
			if (static_cast<int>(std::floor(index/8)) == 6)
			{
				if (m_pieces[index - 8] == nullptr && m_pieces[index - 16] == nullptr)
				{
					return_value.emplace_back(m_pieces[index]->get_piece_type(),
						index, static_cast<uint8_t>(index + 16));
				}
			}
			if (!out_of_bounds(index - 8))
			{
				if (m_pieces[index - 8] == nullptr)
				{
					return_value.emplace_back(m_pieces[index]->get_piece_type(), 
						index, static_cast<uint8_t>(index - 8));
				}
				if (m_pieces[index - 7] != nullptr)
				{
					if (m_pieces[index - 7]->is_white())
					{
						return_value.emplace_back(m_pieces[index]->get_piece_type(),
							index, static_cast<uint8_t>(index - 7));
					}
				}
			}
			if (!out_of_bounds(index - 9))
			{
				if (m_pieces[index - 9] != nullptr)
				{
					if (m_pieces[index - 9]->is_white())
					{
						return_value.emplace_back(m_pieces[index]->get_piece_type(), 
							index, static_cast<uint8_t>(index - 9));
					}
				}
			}
		}
	}
	return return_value;
}
void Board::make_move(const Move& move)
{
	//will need to check for casteling and en pesant before swapping
	std::swap(m_pieces[move.m_start_pos], m_pieces[move.m_end_pos]);
	m_pieces[move.m_start_pos] = nullptr;
	m_is_whites_turn = !m_is_whites_turn;
	m_past_moves.push_back(move);

	if((move.m_piece_type & piece_types::Pawn) == piece_types::Pawn)
	{
		if(move.m_end_pos - move.m_start_pos == 16)
		{
			m_en_pesant_target = move.m_end_pos;
		}
		else
		{
			m_en_pesant_target = -1;
		}
		m_num_half_moves = 0;
	}
	else
	{
		m_en_pesant_target = -1;
		++m_num_half_moves;
	}

	if(!Piece::is_white(move.m_piece_type))
	{
		++m_num_full_moves;
		if((move.m_piece_type & piece_types::King) == piece_types::King)
		{
			
		}
	}
}

