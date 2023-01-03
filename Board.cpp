#include "Board.hpp"
std::vector<std::string> split(const std::string& str, const char& sep)
{
	std::vector<std::string> str_blocks;
	std::stringstream ss(str);
	std::string buffer;
	while (std::getline(ss, buffer, sep)) {
		str_blocks.push_back(buffer);
	}
	return str_blocks;
}

Board::Board()
{
	m_s_null_piece = new Piece();
}
Board::~Board()
{
	for (const auto& i : m_pieces)
		delete i.second;
	delete m_s_null_piece;
}

Piece* Board::get_piece_at_position(const sf::Vector2i& position) const
{
	auto key_val_pair = m_pieces.find(position);
	if(key_val_pair != m_pieces.end())
	{
		return key_val_pair->second;
	}
	else
	{
		//returns a pointer to a null piece which is used to show that there
		//is nothing at that given position
		return m_s_null_piece;
	}
}
std::map<sf::Vector2i, Piece*> Board::get_all_pieces() const
{
	return m_pieces;
}
void Board::add_piece(Piece* piece)
{
	m_pieces.push_back(piece);
}

void Board::set_up_board_from_FEN(const std::string& FEN)
{
	std::vector<std::string> FEN_blocks = split(FEN, ' ');
	assert(FEN_blocks.size() == 6);
	for(std::size_t i = 0; i < FEN_blocks[0].size();++i)
	{
		if(std::isdigit(FEN_blocks[0][i]))
		{
			
		}
	}
}
