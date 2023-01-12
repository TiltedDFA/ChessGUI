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

ExtendedBoard::ExtendedBoard()
	:Board()
{
	m_board_spr.setTexture(TextureManager::get_texture(BOARD_TEXTURE_PATH));
	m_board_spr.setPosition(sf::Vector2f(0, 0));
}